#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

namespace ft {

template <class T>
class _tree_node
{
  public:
	typedef _tree_node<T>* pointer;
	typedef T              _node_value_type;

	pointer          _left;
	pointer          _right;
	pointer          _parent;
	_node_value_type _value;
	bool             _is_black;

	_tree_node() : _left(NULL), _right(NULL), _parent(NULL), _value(0), _is_black(false){};
};


template <class T, class Comp, class Allocator>
class _rbtree
{
  public:
	typedef T              node_value_type;
	typedef Comp           value_compare;
	typedef Allocator      allocator_type;
	typedef _tree_node<T>  node_type;
	typedef _tree_node<T>* node_pointer;

  private:
	node_pointer   _begin_node;
	node_pointer   _nil_node;
	value_compare  _comp;
	allocator_type _alloc;

  public:
	_rbtree()
	{
		_nil_node   = new node_type;
		_begin_node = _nil_node;
	};
	~_rbtree(){};
	_rbtree(_rbtree const& other);
	_rbtree& operator=(_rbtree const& other);

	std::string   _node_to_dir(node_pointer& v, std::string dirprefix, bool is_right);
	node_pointer& _find_parent(node_pointer p);

  public:
	void insert(const node_value_type& v);
	void display();
};


template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::insert(const _rbtree<T, Comp, Allocator>::node_value_type& value)
{
	node_pointer new_   = new node_type;
	node_pointer parent = _nil_node;

	for (node_pointer current = _begin_node; current != _nil_node;) {
		parent = current;
		if (value < current->_value) {
			current = current->_left;
		} else {
			current = current->_right;
		}
	}
	if (parent == _nil_node) {
		_begin_node = new_;
	} else if (value < parent->_value) {
		parent->_left = new_;
	} else {
		parent->_right = new_;
	}
	new_->_parent   = parent;
	new_->_right    = _nil_node;
	new_->_left     = _nil_node;
	new_->_value    = value;
	new_->_is_black = false;
}

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
std::string _rbtree<T, Comp, Allocator>::_node_to_dir(
    _rbtree<T, Comp, Allocator>::node_pointer& v, std::string dirprefix, bool is_right)
{
	if (v == _nil_node)
		return "";

	std::stringstream current_dirname;
	current_dirname << dirprefix << (is_right ? "R_" : "L_") << v->_value;

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

	_node_to_dir(v->_right, dirprefix + "/", true);
	_node_to_dir(v->_left, dirprefix + "/", false);
	return dirprefix;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::display()
{
	std::string dirpath;
	std::string cmd;
	dirpath = _node_to_dir(_begin_node, "./", true);

	setenv("LS_COLORS", "di=00;91:ow=30;107", 1); /* set Red & Black color */
	cmd = "tree -C " + dirpath;
	system(cmd.c_str());
	cmd = "rm -Rf " + dirpath;
	system(cmd.c_str());
}

} // namespace ft

#endif /* RBTREE_HPP */
