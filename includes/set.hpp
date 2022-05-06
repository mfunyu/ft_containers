#ifndef SET_HPP
#define SET_HPP

#include "algorithm.hpp"
#include "pair.hpp"
#include "rbtree.hpp"
#include "reverse_iterator.hpp"
#include <functional>

namespace ft {

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set
{
  public:
	typedef Key            key_type;
	typedef Key            value_type;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Compare        key_compare;
	typedef Compare        value_compare;
	typedef Allocator      allocator_type;

	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;

  private:
	typedef _rbtree<const value_type, key_type, value_compare, allocator_type> _base;

	_base     _tree;
	Compare   _comp;
	Allocator _alloc;

  public:
	typedef typename _base::iterator             iterator;
	typedef typename _base::const_iterator       const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// (constructor)
	explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator());
	template <class InputIt>
	set(InputIt first, InputIt last, const Compare& comp = Compare(),
	    const Allocator& alloc                                  = Allocator(),
	    typename enable_if<!is_integral<InputIt>::value>::type* = 0);
	set(const set& other);
	// (destructor)
	~set() {}
	set&           operator=(const set& other);
	allocator_type get_allocator() const { return _alloc; }

	// ------------------------------- Iterators ------------------------------- //
	iterator               begin() { return _tree.begin(); }
	const_iterator         begin() const { return _tree.begin(); }
	iterator               end() { return _tree.end(); }
	const_iterator         end() const { return _tree.end(); }
	reverse_iterator       rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
	reverse_iterator       rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return reverse_iterator(begin()); }
	// -------------------------------- Capacity ------------------------------- //
	bool      empty() const { return _tree.empty(); }
	size_type size() const { return _tree.size(); }
	size_type max_size() const { return _tree.max_size(); }
	// ------------------------------- Modifiers ------------------------------- //
	void clear() { _tree.clear(); }
	// insert
	ft::pair<iterator, bool> insert(const value_type& value) { return _tree.insert(value); }
	iterator insert(iterator hint, const value_type& value) { return _tree.insert(hint, value); }
	template <class InputIt>
	void insert(InputIt first, InputIt last)
	{
		_tree.insert(first, last);
	}
	// erase
	void      erase(iterator pos) { _tree.erase(pos); }
	void      erase(iterator first, iterator last) { _tree.erase(first, last); }
	size_type erase(const Key& key) { return _tree.erase(key); }
	// swap
	void swap(set& other) { _tree.swap(other._tree); }
	// --------------------------------- Lookup -------------------------------- //
	size_type                count(const Key& key) const { return (find(key) == end() ? 0 : 1); }
	iterator                 find(const Key& key) { return _tree.find(key); }
	const_iterator           find(const Key& key) const { return _tree.find(key); }
	pair<iterator, iterator> equal_range(const Key& key) { return _tree.equal_range(key); }
	pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		return _tree.equal_range(key);
	}
	iterator       lower_bound(const Key& key) { return _tree.lower_bound(key); }
	const_iterator lower_bound(const Key& key) const { return _tree.lower_bound(key); }
	iterator       upper_bound(const Key& key) { return _tree.upper_bound(key); }
	const_iterator upper_bound(const Key& key) const { return _tree.upper_bound(key); }
	// ------------------------------- Observers ------------------------------- //
	key_compare   key_comp() const { return _comp; }
	value_compare value_comp() const { return _comp; }
};

template <class Key, class Comp, class Alloc>
set<Key, Comp, Alloc>::set(const Comp& comp, const Alloc& alloc) :
    _tree(comp, alloc), _comp(comp), _alloc(alloc)
{}

template <class Key, class Comp, class Alloc>
template <class InputIt>
set<Key, Comp, Alloc>::set(InputIt first, InputIt last, const Comp& comp, const Alloc& alloc,
    typename enable_if<!is_integral<InputIt>::value>::type*) :
    _tree(comp, alloc),
    _comp(comp), _alloc(alloc)
{
	insert(first, last);
}

template <class Key, class Comp, class Alloc>
set<Key, Comp, Alloc>::set(set<Key, Comp, Alloc> const& other) :
    _tree(other._tree), _comp(other._comp), _alloc(other._alloc)
{}

template <class Key, class Comp, class Alloc>
set<Key, Comp, Alloc>& set<Key, Comp, Alloc>::operator=(set const& other)
{
	if (this != &other) {
		_tree  = other._tree;
		_comp  = other._comp;
		_alloc = other._alloc;
	}
	return *this;
}

/* -------------------------------------------------------------------------- */
/*                            Non-member functions                            */
/* -------------------------------------------------------------------------- */
template <class Key, class Compare, class Alloc>
bool operator==(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class Compare, class Alloc>
bool operator!=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class Compare, class Alloc>
bool operator<=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator>=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return !(lhs < rhs);
}

/* -------------------------------------------------------------------------- */
/*                                  std::swap                                 */
/* -------------------------------------------------------------------------- */
template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft

#endif /* SET_HPP */
