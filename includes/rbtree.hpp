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
_NodePtr _tree_min_(_NodePtr ptr, _NodePtr _nil_node)
{
	while (ptr->_left != _nil_node) {
		ptr = ptr->_left;
	}
	return ptr;
}

template <class _NodePtr>
_NodePtr _tree_max_(_NodePtr ptr, _NodePtr _nil_node)
{
	while (ptr->_right != _nil_node) {
		ptr = ptr->_right;
	}
	return ptr;
}

template <class _NodePtr>
_NodePtr _tree_next_(_NodePtr ptr, _NodePtr _nil_node)
{
	if (ptr->_right != _nil_node) {
		return _tree_min_(ptr->_right, _nil_node);
	}
	while (!_is_left_child_(ptr)) {
		ptr = ptr->_parent;
	}
	return ptr->_parent;
}

template <class _NodePtr>
_NodePtr _tree_prev_(_NodePtr ptr, _NodePtr _nil_node)
{
	if (ptr->_left != _nil_node) {
		return _tree_max_(ptr->_left, _nil_node);
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
	typedef Comp                    value_compare;
	typedef Allocator               allocator_type;
	typedef _tree_node<value_type>  node_type;
	typedef _tree_node<value_type>* node_pointer;

	typedef _rbtree_iterator<value_type, node_pointer>       iterator;
	typedef _rbtree_iterator<const value_type, node_pointer> const_iterator;

	typedef typename Allocator::template rebind<node_type>::other node_allocator;

  private:
	node_pointer   _begin_node;
	node_pointer   _nil_node;
	value_compare  _comp;
	allocator_type _alloc;

  public:
	_rbtree();
	~_rbtree(){};
	_rbtree(_rbtree const& other);
	_rbtree& operator=(_rbtree const& other);

	node_pointer _find(const value_type& value) const;
	node_pointer _insert(const value_type& value);
	node_pointer _delete(const value_type& value);
	void         _display(std::string func_name = "", int line = -1) const;

	/* ------------------------------ Iterators ----------------------------- */
	iterator       begin() { return iterator(_begin_node, _nil_node); }
	const_iterator begin() const { return iterator(_begin_node, _nil_node); }
	iterator       end() { return iterator(_tree_max_(_begin_node, _nil_node), _nil_node); }
	const_iterator end() const { return iterator(_tree_max_(_begin_node, _nil_node), _nil_node); }

  private:
	node_pointer _init_tree_node_(value_type value);

	/* ----------------------------- algorithms ----------------------------- */
	node_pointer _find_recursive_(const node_pointer ptr, const value_type& value) const;
	void         _transplant_(node_pointer old_ptr, node_pointer new_ptr);
	void         _rotate_left_(node_pointer ptr);
	void         _rotate_right_(node_pointer ptr);
	void         _insert_fixup_(node_pointer ptr);
	void         _delete_fixup_(node_pointer ptr);

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
_rbtree<T, Comp, Allocator>::_rbtree()
{
	node_allocator node_alloc;
	_nil_node            = node_alloc.allocate(1);
	_nil_node->_is_black = true;
	_nil_node->_parent   = _nil_node;
	_nil_node->_left     = _nil_node;
	_nil_node->_right    = _nil_node;
	_begin_node          = _nil_node;
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>::_rbtree(_rbtree<T, Comp, Allocator> const& other)
{
	node_allocator node_alloc;
	_nil_node   = node_alloc.allocate(1);
	_nil_node   = other._nil_node;
	_begin_node = other._begin_node;
	_alloc      = other._alloc;
	_comp       = other._comp;
}

template <class T, class Comp, class Allocator>
_rbtree<T, Comp, Allocator>&
_rbtree<T, Comp, Allocator>::operator=(_rbtree<T, Comp, Allocator> const& other)
{
	if (this != &other) {
		node_allocator node_alloc;
		_nil_node   = node_alloc.allocate(1);
		_nil_node   = other._nil_node;
		_begin_node = other._begin_node;
		_alloc      = other._alloc;
		_comp       = other._comp;
	}
	return *this;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_insert(const _rbtree<T, Comp, Allocator>::value_type& value)
{
	node_pointer new_   = _init_tree_node_(value);
	node_pointer parent = _nil_node;

	for (node_pointer current = _begin_node; current != _nil_node;) {
		parent = current;
		if (_comp(value, current->_value)) {
			current = current->_left;
		} else {
			current = current->_right;
		}
	}
	if (parent == _nil_node) {
		_begin_node = new_;
	} else if (_comp(value, parent->_value)) {
		parent->_left = new_;
	} else {
		parent->_right = new_;
	}
	new_->_parent = parent;
	_display(__FUNCTION__, __LINE__);
	_insert_fixup_(new_);
	return new_;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_find(const _rbtree<T, Comp, Allocator>::value_type& value) const
{
	return _find_recursive_(_begin_node, value);
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_delete(const _rbtree<T, Comp, Allocator>::value_type& value)
{
	node_pointer ptr              = _find(value);
	node_pointer fix_trigger_node = ptr;
	node_pointer child_to_recolor;
	bool         original_color = _is_black_(fix_trigger_node);

	if (ptr->_left == _nil_node) {
		child_to_recolor = ptr->_right;
		_transplant_(ptr, ptr->_right);
	} else if (ptr->_right == _nil_node) {
		child_to_recolor = ptr->_left;
		_transplant_(ptr, ptr->_left);
	} else {
		fix_trigger_node = _tree_min_(ptr->_right, _nil_node);
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
	return ptr;
}

/* -------------------------------------------------------------------------- */
/*                              private functions                             */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_init_tree_node_(_rbtree<T, Comp, Allocator>::value_type value)
{
	node_allocator node_alloc;
	node_pointer   ptr = node_alloc.allocate(1);
	ptr->_parent       = _nil_node;
	ptr->_right        = _nil_node;
	ptr->_left         = _nil_node;
	ptr->_value        = value;
	ptr->_is_black     = false;

	return ptr;
}

/* -------------------------------------------------------------------------- */
/*                                 algorithms                                 */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_find_recursive_(const _rbtree<T, Comp, Allocator>::node_pointer ptr,
    const _rbtree<T, Comp, Allocator>::value_type& value) const
{
	node_pointer found;

	if (ptr == _nil_node) {
		return NULL;
	} else if (ptr->_value == value) {
		return ptr;
	}

	found = _find_recursive_(ptr->_right, value);
	if (found) {
		return found;
	}
	found = _find_recursive_(ptr->_left, value);
	return found;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_transplant_(_rbtree<T, Comp, Allocator>::node_pointer old_ptr,
    _rbtree<T, Comp, Allocator>::node_pointer                                            new_ptr)
{
	if (old_ptr->_parent == _nil_node) {
		_begin_node = new_ptr;
	} else if (_is_left_child_(old_ptr)) {
		old_ptr->_parent->_left = new_ptr;
	} else {
		old_ptr->_parent->_right = new_ptr;
	}
	new_ptr->_parent = old_ptr->_parent;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_rotate_left_(const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	node_pointer child = ptr->_right;
	ptr->_right        = child->_left;
	if (ptr->_right != _nil_node) {
		ptr->_right->_parent = ptr;
	}

	node_pointer parent = ptr->_parent;
	child->_parent      = parent;
	if (parent == _nil_node) {
		_begin_node = child;
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
void _rbtree<T, Comp, Allocator>::_rotate_right_(
    const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	_display(__FUNCTION__, __LINE__);
	node_pointer child = ptr->_left;
	ptr->_left         = child->_right;
	if (ptr->_right != _nil_node) {
		ptr->_right->_parent = ptr;
	}
	node_pointer parent = ptr->_parent;
	child->_parent      = parent;
	if (parent == _nil_node) {
		_begin_node = child;
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
void _rbtree<T, Comp, Allocator>::_insert_fixup_(_rbtree<T, Comp, Allocator>::node_pointer ptr)
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
	_begin_node->_is_black = true;
	_display(__FUNCTION__, __LINE__);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_delete_fixup_(
    const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	node_pointer cousin;

	while (ptr != _begin_node && _is_black_(ptr)) {
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
			ptr = _begin_node;
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
			ptr = _begin_node;
		}
	}
	ptr->_is_black = true;
}

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
int _rbtree<T, Comp, Allocator>::_check_tree_recursive_(
    _rbtree<T, Comp, Allocator>::node_pointer ptr, int black_counts, int& invalid) const
{
	if (ptr == _nil_node) {
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
	if (_is_red_(_begin_node)) {
		std::cerr << "2. root must be black" << std::endl;
		++invalid;
	}
	node_pointer ptr = _begin_node;
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
    const _rbtree<T, Comp, Allocator>::node_pointer& v, std::string dirprefix, bool is_right) const
{
	if (v == _nil_node)
		return "";

	std::stringstream current_dirname;
	current_dirname << dirprefix << (is_right ? "-R_" : "_L_") << v->_value;

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
	dirpath = _node_to_dir_(_begin_node, "./", true);

	std::cout << __FILE__ << ":" << line << " (" << func_name << ")" << std::endl;
	if (dirpath == "") {
		std::cerr << "Error: root deleted" << std::endl;
		exit(1);
	}

	setenv("LS_COLORS", "di=00;91:ow=30;107", 1); /* set Red & Black color */
	cmd = "tree -C --noreport " + dirpath;
	system(cmd.c_str());
	cmd = "rm -Rf " + dirpath;
	system(cmd.c_str());
	_check_tree_validity_();
}

} // namespace ft

#endif /* RBTREE_HPP */
