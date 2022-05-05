#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "type_traits.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

namespace ft {

/* -------------------------------------------------------------------------- */
/*                                  Tree Node                                 */
/* -------------------------------------------------------------------------- */
template <class T>
class _tree_node
{
  public:
	_tree_node* _parent;
	_tree_node* _right;
	_tree_node* _left;
	T           _value;
	bool        _is_black;

	_tree_node() : _parent(NULL), _right(NULL), _left(NULL), _is_black(false) {}
	_tree_node(const T& value) :
	    _parent(NULL), _right(NULL), _left(NULL), _value(value), _is_black(false)
	{}
	_tree_node(_tree_node const& other) :
	    _parent(other._parent), _right(other._right), _left(other._left), _value(other._value),
	    _is_black(other._is_black)
	{}
	_tree_node& operator=(_tree_node const& other)
	{
		if (*this != other) {
			_left     = other._left;
			_right    = other._right;
			_parent   = other._parent;
			_value    = other._value;
			_is_black = other._is_black;
		}
		return *this;
	}
};

namespace {

/* -------------------------------------------------------------------------- */
/*                                    Utils                                   */
/* -------------------------------------------------------------------------- */

template <class _NodePtr>
bool _is_left_child_(const _NodePtr ptr)
{
	return (ptr == ptr->_parent->_left);
}

template <class _NodePtr>
bool _is_right_child_(const _NodePtr ptr)
{
	return (ptr == ptr->_parent->_right);
}

template <class _NodePtr>
bool _is_black_(const _NodePtr ptr)
{
	return (ptr->_is_black);
}

template <class _NodePtr>
bool _is_red_(const _NodePtr ptr)
{
	return (!ptr->_is_black);
}

template <class _NodePtr>
_NodePtr _tree_min_(_NodePtr ptr, _NodePtr _nil)
{
	while (ptr->_left != _nil) {
		ptr = ptr->_left;
	}
	return ptr;
}

template <class _NodePtr>
_NodePtr _tree_max_(_NodePtr ptr, _NodePtr _nil)
{
	while (ptr->_right != _nil) {
		ptr = ptr->_right;
	}
	return ptr;
}

template <class _NodePtr>
_NodePtr _tree_next_(_NodePtr ptr, _NodePtr _nil)
{
	if (ptr->_right != _nil) {
		return _tree_min_(ptr->_right, _nil);
	}
	while (!_is_left_child_(ptr)) {
		ptr = ptr->_parent;
	}
	return ptr->_parent;
}

template <class _NodePtr>
_NodePtr _tree_prev_(_NodePtr ptr, _NodePtr _nil)
{
	if (ptr->_left != _nil) {
		return _tree_max_(ptr->_left, _nil);
	}
	while (!_is_right_child_(ptr)) {
		ptr = ptr->_parent;
	}
	return ptr->_parent;
}

} // namespace

/* -------------------------------------------------------------------------- */
/*                               RBtree Iterator                              */
/* -------------------------------------------------------------------------- */
template <class T, class NodeType>
class _rbtree_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
  public:
	typedef NodeType*                                                  iterator_type;
	typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
	typedef typename iterator_traits<iterator_type>::value_type        node_type;
	typedef typename iterator_traits<iterator_type>::pointer           node_ptr;
	typedef typename iterator_traits<iterator_type>::reference         node_ref;
	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

	typedef T           value_type;
	typedef value_type& reference;
	typedef value_type* pointer;

  private:
	node_ptr _current_;
	node_ptr _nil_;

  public:
	_rbtree_iterator() : _current_(NULL), _nil_(NULL) {}
	_rbtree_iterator(node_ptr current, node_ptr nil) : _current_(current), _nil_(nil) {}
	_rbtree_iterator(_rbtree_iterator const& other) : _current_(other._current_), _nil_(other._nil_)
	{}
	_rbtree_iterator& operator=(_rbtree_iterator const& other)
	{
		if (this != &other) {
			_current_ = other._current_;
			_nil_     = other._nil_;
		}
		return *this;
	}

	/* -------------------------- Access operators -------------------------- */
	node_ptr  base() const { return _current_; }
	reference operator*() const { return _current_->_value; }
	pointer   operator->() const { return &_current_->_value; }
	/* ------------------------ Arithmetic operators ------------------------ */
	_rbtree_iterator& operator++()
	{
		_current_ = _tree_next_(_current_, _nil_);
		return *this;
	}
	_rbtree_iterator operator++(int)
	{
		_rbtree_iterator _tmp(*this);
		++(*this);
		return _tmp;
	}
	_rbtree_iterator& operator--()
	{
		_current_ = _tree_prev_(_current_, _nil_);
		return *this;
	}
	_rbtree_iterator operator--(int)
	{
		_rbtree_iterator _tmp(*this);
		--(*this);
		return _tmp;
	}
	template <class U>
	bool operator==(const _rbtree_iterator<U, NodeType>& other) const
	{
		return _current_ == other.base();
	}
	template <class U>
	bool operator!=(const _rbtree_iterator<U, NodeType>& other) const
	{
		return !(*this == other);
	}

	operator _rbtree_iterator<const T, node_type>(void) const
	{
		return _rbtree_iterator<const T, node_type>(_current_, _nil_);
	}

	/* ------------------------ Non-member functions ------------------------ */
	friend bool operator==(const _rbtree_iterator& _x, const _rbtree_iterator& _y)
	{
		return _x._current_ == _y._current_;
	}
	friend bool operator!=(const _rbtree_iterator& _x, const _rbtree_iterator& _y)
	{
		return !(_x == _y);
	}
};

/* -------------------------------------------------------------------------- */
/*                                   RBtree                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Comp, class Allocator>
class _rbtree
{
  public:
	typedef T                       value_type;
	typedef typename T::first_type  key_type;
	typedef Comp                    value_compare;
	typedef Allocator               allocator_type;
	typedef _tree_node<value_type>  node_type;
	typedef _tree_node<value_type>* node_ptr;

	typedef _rbtree_iterator<value_type, node_type>       iterator;
	typedef _rbtree_iterator<const value_type, node_type> const_iterator;

	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;

	typedef typename Allocator::template rebind<node_type>::other node_allocator;
	typedef std::allocator_traits<node_allocator>                 node_traits;

  private:
	node_ptr _nil;
	node_ptr _begin;
	node_ptr _end;

	value_compare  _comp;
	node_allocator _alloc;
	size_type      _size;

  public:
	_rbtree(const Comp& comp, const Allocator& alloc);
	~_rbtree();
	_rbtree(_rbtree const& other);
	_rbtree&       operator=(_rbtree const& other);
	allocator_type get_allocator() const { return allocator_type(_alloc); }

	/* ------------------------------ Iterators ----------------------------- */
	iterator       begin() { return iterator(_begin, _nil); }
	const_iterator begin() const { return const_iterator(_begin, _nil); }
	iterator       end() { return iterator(_end, _nil); }
	const_iterator end() const { return const_iterator(_end, _nil); }

	/* ------------------------------ Capacity ------------------------------ */
	bool      empty() const { return _root() == _nil; }
	size_type size() const { return _size; }
	size_type max_size() const
	{
		return std::min<size_type>(
		    node_traits::max_size(node_allocator()), std::numeric_limits<difference_type>::max());
	}

	/* ------------------------------ Modifiers ----------------------------- */
	void clear();
	// insert
	ft::pair<iterator, bool> _insert(const value_type& value);
	iterator                 _insert(iterator hint, const value_type& value);
	template <class InputIt>
	void _insert(InputIt first, InputIt last);
	// erase
	iterator erase(iterator pos);
	void     erase(iterator first, iterator last);
	template <class _Key>
	size_type erase(const _Key& value);
	// swap
	void swap(_rbtree& other);

	/* ------------------------------- Lookup ------------------------------- */
	iterator       find(const key_type& key) { return iterator(__find_equal(key), _nil); }
	const_iterator find(const key_type& key) const
	{
		return const_iterator(__find_equal(key), _nil);
	}
	pair<iterator, iterator> equal_range(const key_type& key) { return __equal_range_unique(key); }
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return __equal_range_unique(key);
	}
	iterator       lower_bound(const key_type& key) { return iterator(__lower_bound(key), _nil); }
	const_iterator lower_bound(const key_type& key) const
	{
		return const_iterator(__lower_bound(key), _nil);
	}
	iterator       upper_bound(const key_type& key) { return iterator(__upper_bound(key), _nil); }
	const_iterator upper_bound(const key_type& key) const
	{
		return const_iterator(__upper_bound(key), _nil);
	}

  private:
	node_ptr _root() const;
	void     _set_root(const node_ptr ptr);
	node_ptr _init_tree_node_(const value_type& value);

	void _destroy_recursive(node_ptr ptr);
	void _destroy_one(node_ptr ptr);

	/* ----------------------------- algorithms ----------------------------- */
	void _transplant_(node_ptr old_ptr, node_ptr new_ptr);
	void _rotate_left_(node_ptr ptr);
	void _rotate_right_(node_ptr ptr);

	node_ptr _find_insert_position(const value_type& value, node_ptr hint = NULL);
	node_ptr _insert_unique(const value_type& value, node_ptr parent);
	void     _insert_fixup_(node_ptr ptr);
	void     _insert_update(const node_ptr new_);
	void     _remove(node_ptr ptr);
	void     _remove_fixup_(node_ptr ptr);

	/* ------------------------------- Lookup ------------------------------- */
	template <class _Key>
	iterator _find(const _Key& value) const;
	template <class _Key>
	pair<iterator, iterator> __equal_range_unique(const _Key& key);
	template <class _Key>
	pair<const_iterator, const_iterator> __equal_range_unique(const _Key& key) const;
	template <class _Key>
	node_ptr __find_equal(const _Key& key) const;
	node_ptr __lower_bound(const key_type& key) const;
	node_ptr __upper_bound(const key_type& key) const;

	/* -------------------------------- debug ------------------------------- */
	void        _display(std::string func_name = "", int line = -1) const;
	int         _check_tree_recursive_(node_ptr ptr, int black_count, int& invalid) const;
	void        _check_tree_validity_() const;
	std::string _node_to_dir_(const node_ptr& value, std::string dirprefix, bool is_right) const;
};

/* -------------------------------------------------------------------------- */
/*                              public functions                              */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::_rbtree(const Comp& comp, const Allocator& alloc) :
    _comp(comp), _alloc(node_allocator(alloc)), _size(0)
{
	_nil = _alloc.allocate(1);
	_alloc.construct(_nil, T());
	_nil->_is_black = true;
	_nil->_parent   = _nil;
	_nil->_left     = _nil;
	_nil->_right    = _nil;

	_end            = _init_tree_node_(T());
	_end->_is_black = true;
	_begin          = _end;
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::~_rbtree()
{
	_destroy_recursive(_end);
	_destroy_one(_nil);
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::_rbtree(_rbtree const& other) :
    _comp(other._comp), _alloc(other._alloc), _size(0)
{
	_nil = _alloc.allocate(1);
	_alloc.construct(_nil, T());
	_nil->_is_black = true;
	_nil->_parent   = _nil;
	_nil->_left     = _nil;
	_nil->_right    = _nil;

	_end   = _init_tree_node_(T());
	_begin = _end;
	_insert(other.begin(), other.end());
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>& _rbtree<T, Comp, Allocator>::operator=(_rbtree const& other)
{
	if (this != &other) {
		_rbtree new_(other);
		swap(new_);
	}
	return *this;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_ptr
_rbtree<T, Comp, Allocator>::_insert_unique(const value_type& value, node_ptr parent)
{
	node_ptr new_ = _init_tree_node_(value);

	if (parent == _end) {
		_set_root(new_);
	} else if (_comp(value, parent->_value)) {
		parent->_left = new_;
	} else {
		parent->_right = new_;
	}
	new_->_parent = parent;
	_insert_fixup_(new_);
	_insert_update(new_);
	return new_;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::clear()
{
	_rbtree new_(_comp, _alloc);
	swap(new_);
}

template <class T, class Comp, class Allocator>
typename ft::pair<typename _rbtree<T, Comp, Allocator>::iterator, bool>
_rbtree<T, Comp, Allocator>::_insert(const value_type& value)
{
	node_ptr ptr = _find_insert_position(value);
	if (ptr != _end && !_comp(ptr->_value, value) && !_comp(value, ptr->_value)) {
		return ft::make_pair(iterator(ptr, _nil), false);
	}
	return ft::make_pair(iterator(_insert_unique(value, ptr), _nil), true);
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::iterator
_rbtree<T, Comp, Allocator>::_insert(iterator hint, const value_type& value)
{
	node_ptr ptr = _find_insert_position(value, hint.base());
	if (ptr != _end && !_comp(ptr->_value, value) && !_comp(value, ptr->_value)) {
		return iterator(ptr, _nil);
	}
	return iterator(_insert_unique(value, ptr), _nil);
}

template <class T, class Comp, class Allocator>
template <class InputIt>
void _rbtree<T, Comp, Allocator>::_insert(InputIt first, InputIt last)
{
	for (; first != last; ++first) {
		_insert(*first);
	}
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::swap(_rbtree& other)
{
	std::swap(_nil, other._nil);
	std::swap(_begin, other._begin);
	std::swap(_end, other._end);
	std::swap(_comp, other._comp);
	std::swap(_alloc, other._alloc);
	std::swap(_size, other._size);
}

template <class T, class Comp, class Allocator>
template <class _Key>
typename _rbtree<T, Comp, Allocator>::iterator
_rbtree<T, Comp, Allocator>::_find(const _Key& key) const
{
	return iterator(__find_equal(key), _nil);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_remove(node_ptr ptr)
{
	node_ptr fix_trigger_node = ptr;
	node_ptr child_to_recolor;
	bool     original_color = _is_black_(fix_trigger_node);

	if (ptr->_left == _nil) {
		child_to_recolor = ptr->_right;
		_transplant_(ptr, ptr->_right);
	} else if (ptr->_right == _nil) {
		child_to_recolor = ptr->_left;
		_transplant_(ptr, ptr->_left);
	} else {
		fix_trigger_node = _tree_min_(ptr->_right, _nil);
		original_color   = _is_black_(fix_trigger_node);
		child_to_recolor = fix_trigger_node->_right;
		if (fix_trigger_node->_parent == ptr) {
			child_to_recolor->_parent = fix_trigger_node;
		} else {
			_transplant_(fix_trigger_node, fix_trigger_node->_right);
			fix_trigger_node->_right          = ptr->_right;
			fix_trigger_node->_right->_parent = fix_trigger_node;
		}
		_transplant_(ptr, fix_trigger_node);
		fix_trigger_node->_left          = ptr->_left;
		fix_trigger_node->_left->_parent = fix_trigger_node;
		fix_trigger_node->_is_black      = ptr->_is_black;
	}

	if (original_color) {
		_remove_fixup_(child_to_recolor);
	}
}

template <class T, class Comp, class Allocator>
template <class _Key>
typename _rbtree<T, Comp, Allocator>::size_type
_rbtree<T, Comp, Allocator>::erase(const _Key& value)
{
	iterator ite = _find(value);
	if (ite == end()) {
		return 0;
	}
	if (begin() == ite) {
		iterator next(ite);
		++next;
		_begin = next.base();
	}
	--_size;
	_remove(ite.base());
	return 1;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::iterator _rbtree<T, Comp, Allocator>::erase(iterator pos)
{
	iterator next(pos);
	++next;
	if (begin() == pos) {
		_begin = next.base();
	}
	--_size;
	_remove(pos.base());
	return next;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::erase(iterator first, iterator last)
{
	while (first != last) {
		first = erase(first);
	}
}

/* -------------------------------------------------------------------------- */
/*                              private functions                             */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_ptr _rbtree<T, Comp, Allocator>::_root() const
{
	return _end->_left;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_ptr
_rbtree<T, Comp, Allocator>::_init_tree_node_(const value_type& value)
{
	node_ptr ptr = _alloc.allocate(1);
	_alloc.construct(ptr, value);
	ptr->_parent   = _nil;
	ptr->_right    = _nil;
	ptr->_left     = _nil;
	ptr->_is_black = false;
	return ptr;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_insert_update(const node_ptr new_)
{
	if (_begin == _end || _comp(new_->_value, _begin->_value)) {
		_begin = new_;
	}
	++_size;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_ptr
_rbtree<T, Comp, Allocator>::_find_insert_position(const value_type& value, node_ptr hint)
{
	node_ptr prev    = _end;
	node_ptr current = _root();

	if (hint && hint != _end) {
		if (_comp(value, hint->_value) && hint->_left == _nil) {
			iterator prev = iterator(hint, _nil);
			// prev < value < hint
			if (prev == begin() || _comp(*--prev, value)) {
				return hint;
			}
		} else if (hint->_right == _nil) {
			iterator next = iterator(hint, _nil);
			// hint < value < next
			if (next == end() || _comp(value, *++next)) {
				return hint;
			}
		}
	}
	for (; current != _nil;) {
		prev = current;
		if (_comp(value, current->_value)) {
			current = current->_left;
		} else if (_comp(current->_value, value)) {
			current = current->_right;
		} else {
			return current;
		}
	}
	return prev;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_set_root(const node_ptr ptr)
{
	ptr->_parent = _end;
	_end->_left  = ptr;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_destroy_recursive(node_ptr ptr)
{
	if (ptr == _nil)
		return;
	_destroy_recursive(ptr->_left);
	_destroy_recursive(ptr->_right);
	_destroy_one(ptr);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_destroy_one(node_ptr ptr)
{
	_alloc.destroy(ptr);
	_alloc.deallocate(ptr, 1);
}

/* -------------------------------------------------------------------------- */
/*                                 algorithms                                 */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_transplant_(node_ptr old_ptr, node_ptr new_ptr)
{
	if (old_ptr->_parent == _end) {
		_set_root(new_ptr);
	} else if (_is_left_child_(old_ptr)) {
		old_ptr->_parent->_left = new_ptr;
	} else {
		old_ptr->_parent->_right = new_ptr;
	}
	new_ptr->_parent = old_ptr->_parent;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_rotate_left_(const node_ptr ptr)
{
	node_ptr child = ptr->_right;
	ptr->_right    = child->_left;
	if (ptr->_right != _nil) {
		ptr->_right->_parent = ptr;
	}

	node_ptr parent = ptr->_parent;
	child->_parent  = parent;
	if (parent == _end) {
		_set_root(child);
	} else if (_is_left_child_(ptr)) {
		parent->_left = child;
	} else {
		parent->_right = child;
	}
	child->_left = ptr;
	ptr->_parent = child;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_rotate_right_(const node_ptr ptr)
{
	node_ptr child = ptr->_left;
	ptr->_left     = child->_right;
	if (ptr->_left != _nil) {
		ptr->_left->_parent = ptr;
	}

	node_ptr parent = ptr->_parent;
	child->_parent  = parent;
	if (parent == _end) {
		_set_root(child);
	} else if (_is_left_child_(ptr)) {
		parent->_left = child;
	} else {
		parent->_right = child;
	}
	child->_right = ptr;
	ptr->_parent  = child;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_insert_fixup_(node_ptr ptr)
{
	node_ptr uncle;
	while (_is_red_(ptr->_parent)) {
		if (_is_left_child_(ptr->_parent)) {
			uncle = ptr->_parent->_parent->_right;
			if (_is_red_(uncle)) {
				ptr->_parent->_is_black   = true;
				uncle->_is_black          = true;
				uncle->_parent->_is_black = false;

				ptr = uncle->_parent;
			} else {
				if (_is_right_child_(ptr)) {
					ptr = ptr->_parent;
					_rotate_left_(ptr);
				}
				ptr->_parent->_is_black          = true;
				ptr->_parent->_parent->_is_black = false;
				_rotate_right_(ptr->_parent->_parent);
			}
		} else {
			uncle = ptr->_parent->_parent->_left;
			if (_is_red_(uncle)) {
				ptr->_parent->_is_black   = true;
				uncle->_is_black          = true;
				uncle->_parent->_is_black = false;

				ptr = uncle->_parent;
			} else {
				if (_is_left_child_(ptr)) {
					ptr = ptr->_parent;
					_rotate_right_(ptr);
				}
				ptr->_parent->_is_black          = true;
				ptr->_parent->_parent->_is_black = false;
				_rotate_left_(ptr->_parent->_parent);
			}
		}
	}
	_root()->_is_black = true;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_remove_fixup_(const node_ptr ptr)
{
	node_ptr brother;

	while (ptr != _root() && _is_black_(ptr)) {
		if (_is_left_child_(ptr)) {
			brother = ptr->_parent->_right;
			if (_is_red_(brother)) {
				brother->_is_black      = true;
				ptr->_parent->_is_black = false;
				_rotate_left_(ptr->_parent);
				brother = ptr->_parent->_right;
			}
			if (_is_black_(brother->_left) && _is_black_(brother->_right)) {
				brother->_is_black = false;
				ptr                = ptr->_parent;
			} else if (_is_black_(brother->_right)) {
				brother->_left->_is_black = true;
				brother->_is_black        = false;
				_rotate_right_(brother);
				brother = ptr->_parent->_right;
			}
			if (_is_red_(brother->_right)) {
				brother->_is_black         = ptr->_parent->_is_black;
				ptr->_parent->_is_black    = true;
				brother->_right->_is_black = true;
				_rotate_left_(ptr->_parent);
				ptr = _root();
			}
		} else {
			brother = ptr->_parent->_left;
			if (_is_red_(brother)) {
				brother->_is_black      = true;
				ptr->_parent->_is_black = false;
				_rotate_left_(ptr->_parent);
				brother = ptr->_parent->_left;
			}
			if (_is_black_(brother->_right) && _is_black_(brother->_left)) {
				brother->_is_black = false;
				ptr                = ptr->_parent;
			} else if (_is_black_(brother->_left)) {
				brother->_right->_is_black = true;
				brother->_is_black         = false;
				_rotate_left_(brother);
				brother = ptr->_parent->_left;
			}
			if (_is_red_(brother->_left)) {
				brother->_is_black        = ptr->_parent->_is_black;
				ptr->_parent->_is_black   = true;
				brother->_left->_is_black = true;
				_rotate_right_(ptr->_parent);
				ptr = _root();
			}
		}
	}
	ptr->_is_black = true;
}

/* -------------------------------------------------------------------------- */
/*                                   Lookups                                  */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
template <class _Key>
typename _rbtree<T, Comp, Allocator>::node_ptr
_rbtree<T, Comp, Allocator>::__find_equal(const _Key& key) const
{
	node_ptr ptr = _root();

	while (ptr != _nil) {
		if (_comp(key, ptr->_value)) {
			ptr = ptr->_left;
		} else if (_comp(ptr->_value, key)) {
			ptr = ptr->_right;
		} else {
			return ptr;
		}
	}
	return _end;
}

template <class T, class Comp, class Allocator>
template <class _Key>
ft::pair<typename _rbtree<T, Comp, Allocator>::iterator,
    typename _rbtree<T, Comp, Allocator>::iterator>
_rbtree<T, Comp, Allocator>::__equal_range_unique(const _Key& key)
{
	node_ptr ptr    = _root();
	node_ptr result = _end;

	while (ptr != _nil) {
		if (_comp(key, ptr->_value)) {
			result = ptr;
			ptr    = ptr->_left;
		} else if (_comp(ptr->_value, key)) {
			ptr = ptr->_right;
		} else {
			if (ptr->_right != _nil) {
				result = _tree_min_(ptr->_right, _nil);
			}
			return ft::make_pair(iterator(ptr, _nil), iterator(result, _nil));
		}
	}
	return ft::make_pair(iterator(result, _nil), iterator(result, _nil));
}

template <class T, class Comp, class Allocator>
template <class _Key>
ft::pair<typename _rbtree<T, Comp, Allocator>::const_iterator,
    typename _rbtree<T, Comp, Allocator>::const_iterator>
_rbtree<T, Comp, Allocator>::__equal_range_unique(const _Key& key) const
{
	node_ptr ptr    = _root();
	node_ptr result = _end;

	while (ptr != _nil) {
		if (_comp(key, ptr->_value)) {
			result = ptr;
			ptr    = ptr->_left;
		} else if (_comp(ptr->_value, key)) {
			ptr = ptr->_right;
		} else {
			if (ptr->_right != _nil) {
				result = _tree_min_(ptr->_right, _nil);
			}
			return ft::make_pair(const_iterator(ptr, _nil), const_iterator(result, _nil));
		}
	}
	return ft::make_pair(const_iterator(result, _nil), const_iterator(result, _nil));
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_ptr
_rbtree<T, Comp, Allocator>::__lower_bound(const key_type& key) const
{
	node_ptr ptr    = _root();
	node_ptr result = _end;

	while (ptr != _nil) {
		if (!_comp(ptr->_value, key)) {
			result = ptr;
			ptr    = ptr->_left;
		} else {
			ptr = ptr->_right;
		}
	}
	return result;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_ptr
_rbtree<T, Comp, Allocator>::__upper_bound(const key_type& key) const
{
	node_ptr ptr    = _root();
	node_ptr result = _end;

	while (ptr != _nil) {
		if (_comp(key, ptr->_value)) {
			result = ptr;
			ptr    = ptr->_left;
		} else {
			ptr = ptr->_right;
		}
	}
	return result;
}

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
int _rbtree<T, Comp, Allocator>::_check_tree_recursive_(
    node_ptr ptr, int black_counts, int& invalid) const
{
	if (ptr == _nil) {
		return black_counts;
	}
	if (ptr->_is_black) {
		++black_counts;
	}
	if (_is_red_(ptr) && (_is_red_(ptr->_left) || _is_red_(ptr->_right))) {
		std::cerr << "4. the children of red must be black" << std::endl;
		++invalid;
	}
	int total;
	total = _check_tree_recursive_(ptr->_right, black_counts, invalid);
	if (total != _check_tree_recursive_(ptr->_left, black_counts, invalid)) {
		std::cerr << "5. count of black nodes must be the same" << std::endl;
		++invalid;
	}
	return total;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_check_tree_validity_() const
{
	int invalid = 0;
	if (_is_red_(_root())) {
		std::cerr << "2. root must be black" << std::endl;
		++invalid;
	}
	node_ptr ptr = _root();
	_check_tree_recursive_(ptr, 0, invalid);
	if (invalid) {
		std::cerr << "\033[31m"
		          << "ERROR: tree is wrong... ;("
		          << "\033[0m" << std::endl;
		// exit(EXIT_FAILURE);
	} else {
		std::cerr << "\033[32m"
		          << "PASS: tree is correct! :)"
		          << "\033[m" << std::endl;
	}
}

template <class T, class Comp, class Allocator>
std::string _rbtree<T, Comp, Allocator>::_node_to_dir_(
    const node_ptr& v, std::string dirprefix, bool is_right) const
{
	if (v == _nil)
		return "";

	std::stringstream current_dirname;
	current_dirname << dirprefix << (is_right ? "-R_" : "_L_") << v->_value.first;

	/* delete all before creating the root directory */
	if (dirprefix == "./") {
		std::string cmd = "rm -Rf " + current_dirname.str();
		system(cmd.c_str());
	}
	dirprefix = current_dirname.str();

	mode_t mode;
	mode = v->_is_black ? 0777 : 0755; /* to create color difference */
	mkdir(dirprefix.c_str(), mode);
	chmod(dirprefix.c_str(), mode);

	_node_to_dir_(v->_right, dirprefix + "/", true);
	_node_to_dir_(v->_left, dirprefix + "/", false);
	return dirprefix;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_display(std::string func_name, int line) const
{
	std::string dirpath;
	std::string cmd;
	dirpath = _node_to_dir_(_root(), "./", true);
	std::cerr << "size: " << _size << std::endl;

	std::cerr << __FILE__ << ":" << line << " (" << func_name << ")" << std::endl;
	if (dirpath == "") {
		std::cerr << "Error: root deleted" << std::endl;
		exit(1);
	}

	setenv("LS_COLORS", "di=00;91:ow=30;107", 1); /* set Red & Black color */
	cmd = "tree -C --noreport " + dirpath + " 1>&2";
	system(cmd.c_str());
	cmd = "rm -Rf " + dirpath;
	system(cmd.c_str());
	_check_tree_validity_();
}

} // namespace ft

#endif /* RBTREE_HPP */
