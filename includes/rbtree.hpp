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

	_tree_node() : _parent(NULL), _right(NULL), _left(NULL), _is_black(false){};
	_tree_node(const T& value) :
	    _parent(NULL), _right(NULL), _left(NULL), _value(value), _is_black(false){};
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
	};

  private:
	_tree_node(_tree_node const& other);
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
bool _is_black_(
    const _NodePtr ptr, typename ft::enable_if<!ft::is_integral<_NodePtr>::value>::type* = 0)
{
	return (ptr->_is_black);
}

bool _is_black_(bool _is_black_)
{
	return (_is_black_);
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
template <class T, class _NodePtr>
class _rbtree_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
  public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T                               value_type;
	typedef value_type&                     reference;
	typedef value_type*                     pointer;

  private:
	_NodePtr _current_;
	_NodePtr _nil_;

  public:
	_rbtree_iterator() : _current_(NULL), _nil_(NULL) {}
	_rbtree_iterator(_NodePtr current, _NodePtr nil) : _current_(current), _nil_(nil) {}
	_rbtree_iterator operator=(_rbtree_iterator const& other)
	{
		if (this != &other) {
			_current_ = other._current_;
			_nil_     = other._nil_;
		}
		return *this;
	}

	/* -------------------------- Access operators -------------------------- */
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
	typedef _tree_node<value_type>* node_pointer;

	typedef _rbtree_iterator<value_type, node_pointer>       iterator;
	typedef _rbtree_iterator<const value_type, node_pointer> const_iterator;

	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;

	typedef typename Allocator::template rebind<node_type>::other node_allocator;
	typedef std::allocator_traits<node_allocator>                 node_traits;

  private:
	node_pointer   _root;
	node_pointer   _nil;
	node_pointer   _begin;
	node_pointer   _end;
	value_compare  _comp;
	node_allocator _alloc;
	size_type      _size;

  public:
	_rbtree(const Comp& comp, const Allocator& alloc);
	~_rbtree();
	_rbtree(_rbtree const& other);
	_rbtree&       operator=(_rbtree const& other);
	allocator_type get_allocator() const { return allocator_type(_alloc); }

	template <class _Key>
	iterator     _find(const _Key& value) const;
	node_pointer _delete(const value_type& value);
	void         _display(std::string func_name = "", int line = -1) const;

	/* ------------------------------ Iterators ----------------------------- */
	iterator       begin() { return iterator(_begin, _nil); }
	const_iterator begin() const { return const_iterator(_begin, _nil); }
	iterator       end() { return iterator(_end, _nil); }
	const_iterator end() const { return const_iterator(_end, _nil); }

	/* ------------------------------ Capacity ------------------------------ */
	bool      empty() const { return _root == _nil; }
	size_type size() const { return _size; };
	size_type max_size() const
	{
		return std::min<size_type>(
		    node_traits::max_size(node_allocator()), std::numeric_limits<difference_type>::max());
	}

	/* ------------------------------ Modifiers ----------------------------- */
	void                     clear() {}
	ft::pair<iterator, bool> _insert(const value_type& value);
	template <class InputIt>
	void _insert(InputIt first, InputIt last);
	void swap(_rbtree& other);

	/* ------------------------------- Lookup ------------------------------- */
	size_type      count(const key_type& key) const {};
	iterator       find(const key_type& key) { return iterator(__equal_range_unique(key), _nil); };
	const_iterator find(const key_type& key) const
	{
		return const_iterator(__equal_range_unique(key), _nil);
	};
	pair<iterator, iterator> equal_range(const key_type& key)
	{
		iterator itr = iterator(__equal_range_unique(key), _nil);
		return ft::make_pair(itr, itr);
	}
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		const_iterator c_itr = const_iterator(__equal_range_unique(key), _nil);
		return ft::make_pair(c_itr, c_itr);
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
	node_pointer _init_tree_node_(const value_type& value);
	void         _insert_update(const node_pointer new_);
	node_pointer _find_insert_position(const value_type& value);
	void         _set_root(const node_pointer ptr);

	void _destroy_recursive(node_pointer ptr);
	void _destroy_one(node_pointer ptr);

	/* ----------------------------- algorithms ----------------------------- */
	void _transplant_(node_pointer old_ptr, node_pointer new_ptr);
	void _rotate_left_(node_pointer ptr);
	void _rotate_right_(node_pointer ptr);
	void _insert_fixup_(node_pointer ptr);
	void _delete_fixup_(node_pointer ptr);

	/* ------------------------------- Lookup ------------------------------- */
	template <class _Key>
	node_pointer __equal_range_unique(const _Key& key) const;
	node_pointer __lower_bound(const key_type& key) const;
	node_pointer __upper_bound(const key_type& key) const;

	/* -------------------------------- debug ------------------------------- */
	int  _check_tree_recursive_(node_pointer ptr, int black_count, int& invalid) const;
	void _check_tree_validity_() const;
	std::string
	_node_to_dir_(const node_pointer& value, std::string dirprefix, bool is_right) const;
};

/* -------------------------------------------------------------------------- */
/*                              public functions                              */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::_rbtree(const Comp& comp, const Allocator& alloc) :
    _comp(comp), _alloc(node_allocator(alloc)), _size(0)
{
	_nil            = _alloc.allocate(1);
	_nil->_is_black = true;
	_nil->_parent   = _nil;
	_nil->_left     = _nil;
	_nil->_right    = _nil;
	_root           = _nil;
	_end            = _init_tree_node_(T());
	_end->_is_black = true;
	_begin          = _end;
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::~_rbtree()
{
	_destroy_recursive(_root);
	_destroy_one(_end);
	_destroy_one(_nil);
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::_rbtree(_rbtree const& other) :
    _comp(other._comp), _alloc(other._alloc), _size(other._size)
{
	_nil   = _alloc.allocate(1);
	_nil   = other._nil;
	_root  = other._root;
	_begin = other._begin;
	_end   = other._end;
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>& _rbtree<T, Comp, Allocator>::operator=(_rbtree const& other)
{
	if (this != &other) {
		_nil   = _alloc.allocate(1);
		_nil   = other._nil;
		_root  = other._root;
		_begin = other._begin;
		_end   = other._end;
		_alloc = other._alloc;
		_comp  = other._comp;
		_size  = other._size;
	}
	return *this;
}

template <class T, class Comp, class Allocator>
typename ft::pair<typename _rbtree<T, Comp, Allocator>::iterator, bool>
_rbtree<T, Comp, Allocator>::_insert(const value_type& value)
{
	iterator ptr = _find(value);
	if (ptr != end()) {
		return ft::make_pair(ptr, false);
	}
	node_pointer new_   = _init_tree_node_(value);
	node_pointer parent = _find_insert_position(value);

	if (parent == _end) {
		_set_root(new_);
	} else if (_comp(value, parent->_value)) {
		parent->_left = new_;
	} else {
		parent->_right = new_;
	}
	new_->_parent = parent;
	_display(__FUNCTION__, __LINE__);
	_insert_fixup_(new_);
	_insert_update(new_);
	return ft::make_pair(iterator(new_, _nil), true);
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
	std::swap(_root, other._root);
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
	return iterator(__equal_range_unique(key), _nil);
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_delete(const value_type& value)
{
	node_pointer ptr              = _find(value);
	node_pointer fix_trigger_node = ptr;
	node_pointer child_to_recolor;
	bool         original_color = _is_black_(fix_trigger_node);

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

	if (_is_black_(original_color)) {
		_delete_fixup_(child_to_recolor);
	}
	--_size;
	return ptr;
}

/* -------------------------------------------------------------------------- */
/*                              private functions                             */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_init_tree_node_(const value_type& value)
{
	node_pointer ptr = _alloc.allocate(1);
	_alloc.construct(ptr, value);
	ptr->_parent   = _nil;
	ptr->_right    = _nil;
	ptr->_left     = _nil;
	ptr->_is_black = false;
	return ptr;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_insert_update(const node_pointer new_)
{
	if (_begin == _end || _comp(new_->_value, _begin->_value)) {
		_begin = new_;
	}
	++_size;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_find_insert_position(const value_type& value)
{
	node_pointer prev = _end;

	for (node_pointer current = _root; current != _nil;) {
		prev = current;
		if (_comp(value, current->_value)) {
			current = current->_left;
		} else {
			current = current->_right;
		}
	}
	return prev;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_set_root(const node_pointer ptr)
{
	_root          = ptr;
	_root->_parent = _end;
	_end->_left    = _root;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_destroy_recursive(node_pointer ptr)
{
	if (ptr == _nil)
		return;
	_destroy_recursive(ptr->_left);
	_destroy_recursive(ptr->_right);
	_destroy_one(ptr);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_destroy_one(node_pointer ptr)
{
	_alloc.destroy(ptr);
	_alloc.deallocate(ptr, 1);
}

/* -------------------------------------------------------------------------- */
/*                                 algorithms                                 */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_transplant_(node_pointer old_ptr, node_pointer new_ptr)
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
void _rbtree<T, Comp, Allocator>::_rotate_left_(const node_pointer ptr)
{
	node_pointer child = ptr->_right;
	ptr->_right        = child->_left;
	if (ptr->_right != _nil) {
		ptr->_right->_parent = ptr;
	}

	node_pointer parent = ptr->_parent;
	child->_parent      = parent;
	if (parent == _end) {
		_set_root(child);
	} else if (_is_left_child_(ptr)) {
		parent->_left = child;
	} else {
		parent->_right = child;
	}
	child->_left = ptr;
	ptr->_parent = child;
	_display(__FUNCTION__, __LINE__);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_rotate_right_(const node_pointer ptr)
{
	_display(__FUNCTION__, __LINE__);
	node_pointer child = ptr->_left;
	ptr->_left         = child->_right;
	if (ptr->_right != _nil) {
		ptr->_right->_parent = ptr;
	}
	node_pointer parent = ptr->_parent;
	child->_parent      = parent;
	if (parent == _end) {
		_set_root(child);
	} else if (_is_left_child_(ptr)) {
		parent->_left = child;
	} else {
		parent->_right = child;
	}
	child->_right = ptr;
	ptr->_parent  = child;
	_display(__FUNCTION__, __LINE__);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_insert_fixup_(node_pointer ptr)
{
	node_pointer uncle;
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
	_root->_is_black = true;
	_display(__FUNCTION__, __LINE__);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_delete_fixup_(const node_pointer ptr)
{
	node_pointer cousin;

	while (ptr != _root && _is_black_(ptr)) {
		if (_is_left_child_(ptr)) {
			cousin = ptr->_parent->_right;
			if (_is_red_(cousin)) {
				cousin->_is_black       = true;
				ptr->_parent->_is_black = false;
				_rotate_left_(ptr->_parent);
				cousin = ptr->_parent->_right;
			}
			if (_is_black_(cousin->_left) && _is_black_(cousin->_right)) {
				cousin->_is_black = false;
				ptr               = ptr->_parent;
			} else if (_is_black_(cousin->_right)) {
				cousin->_left->_is_black = true;
				cousin->_is_black        = false;
				_rotate_right_(cousin);
				cousin = ptr->_parent->_right;
			}
			cousin->_is_black         = ptr->_parent->_is_black;
			ptr->_parent->_is_black   = true;
			cousin->_right->_is_black = true;
			_rotate_left_(ptr->_parent);
			ptr = _root;
		} else {
			cousin = ptr->_parent->_left;
			if (_is_red_(cousin)) {
				cousin->_is_black       = true;
				ptr->_parent->_is_black = false;
				_rotate_left_(ptr->_parent);
				cousin = ptr->_parent->_left;
			}
			if (_is_black_(cousin->_right) && _is_black_(cousin->_left)) {
				cousin->_is_black = false;
				ptr               = ptr->_parent;
			} else if (_is_black_(cousin->_left)) {
				cousin->_right->_is_black = true;
				cousin->_is_black         = false;
				_rotate_left_(cousin);
				cousin = ptr->_parent->_left;
			}
			cousin->_is_black        = ptr->_parent->_is_black;
			ptr->_parent->_is_black  = true;
			cousin->_left->_is_black = true;
			_rotate_right_(ptr->_parent);
			ptr = _root;
		}
	}
	ptr->_is_black = true;
}

/* -------------------------------------------------------------------------- */
/*                                   Lookups                                  */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
template <class _Key>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::__equal_range_unique(const _Key& key) const
{
	node_pointer ptr = _root;

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
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::__lower_bound(const key_type& key) const
{
	node_pointer ptr = _root;
	node_pointer result;

	while (ptr != _nil) {
		if (!_comp(ptr->_value, key)) {
			result = ptr;
			ptr    = ptr->_left;
		} else {
			ptr = ptr->_right;
		}
	}
	return _end;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::__upper_bound(const key_type& key) const
{
	node_pointer ptr = _root;
	node_pointer result;

	while (ptr != _nil) {
		if (_comp(ptr->_value, key)) {
			result = ptr;
			ptr    = ptr->_right;
		} else {
			ptr = ptr->_left;
		}
	}
	return _end;
}

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
int _rbtree<T, Comp, Allocator>::_check_tree_recursive_(
    node_pointer ptr, int black_counts, int& invalid) const
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
	if (_is_red_(_root)) {
		std::cerr << "2. root must be black" << std::endl;
		++invalid;
	}
	node_pointer ptr = _root;
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
    const node_pointer& v, std::string dirprefix, bool is_right) const
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
#ifdef DEBUG
	std::string dirpath;
	std::string cmd;
	dirpath = _node_to_dir_(_root, "./", true);
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
#endif
}

} // namespace ft

#endif /* RBTREE_HPP */
