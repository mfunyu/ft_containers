#ifndef MAP_HPP
#define MAP_HPP

#include "algorithm.hpp"
#include "iterators.hpp"
#include "pair.hpp"
#include "rbtree.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<pair<const Key, T> > >
class map
{
  public:
	typedef Key                               key_type;
	typedef T                                 mapped_type;
	typedef pair<const Key, T>                value_type;
	typedef std::size_t                       size_type;
	typedef std::ptrdiff_t                    difference_type;
	typedef Compare                           key_compare;
	typedef Allocator                         allocator_type;
	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;

	class value_compare
	{
	  public:
		typedef bool       result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

		key_compare comp;
		value_compare(key_compare c) : comp(c){};

		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return comp(lhs.first, rhs.first);
		};
		bool operator()(const value_type& lhs, const key_type& rhs) const
		{
			return comp(lhs.first, rhs);
		};
		bool operator()(const key_type& lhs, const value_type& rhs) const
		{
			return comp(lhs, rhs.first);
		};
	};

  private:
	typedef _rbtree<value_type, value_compare, allocator_type> _base;

	key_compare   _key_comp;
	value_compare _value_comp;
	_base         _tree;

  public:
	typedef typename _base::iterator             iterator;
	typedef typename _base::const_iterator       const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// (constructor)
	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator());
	template <class InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(),
	    const Allocator& alloc                                  = Allocator(),
	    typename enable_if<!is_integral<InputIt>::value>::type* = 0);
	map(map const& other);
	// (destructor)
	~map(){};
	map&           operator=(map const& other);
	allocator_type get_allocator() const { return allocator_type(_tree.get_allocator()); }
	// ---------------------------- Elements access ---------------------------- //
	// at
	T&       at(const Key& key);
	const T& at(const Key& key) const;
	// operator[]
	T& operator[](const Key& key) { return insert(ft::make_pair(key, T())).first->second; };
	// ------------------------------- Iterators ------------------------------- //
	iterator               begin() { return _tree.begin(); }
	const_iterator         begin() const { return _tree.begin(); }
	iterator               end() { return _tree.end(); }
	const_iterator         end() const { return _tree.end(); }
	reverse_iterator       rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
	reverse_iterator       rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return reverse_iterator(begin()); }
	/* -------------------------------- Capacity ------------------------------- */
	bool      empty() const { return _tree.empty(); }
	size_type size() const { return _tree.size(); }
	size_type max_size() const { return _tree.max_size(); }
	/* ------------------------------- Modifiers ------------------------------- */
	void clear() { _tree.clear(); }
	// insert
	ft::pair<iterator, bool> insert(const value_type& value) { return _tree._insert(value); };
	iterator insert(iterator hint, const value_type& value) { return _tree._insert(hint, value); };
	template <class InputIt>
	void insert(InputIt first, InputIt last)
	{
		_tree._insert(first, last);
	}
	// erase
	void      erase(iterator pos) { _tree.erase(pos); };
	void      erase(iterator first, iterator last) { _tree.erase(first, last); };
	size_type erase(const Key& key) { _tree.erase(key); };
	// swap
	void swap(map& other) { _tree.swap(other._tree); };
	/* --------------------------------- Lookup -------------------------------- */
	size_type                count(const Key& key) const { return (find(key) == end() ? 0 : 1); }
	iterator                 find(const Key& key) { return _tree.find(key); };
	const_iterator           find(const Key& key) const { return _tree.find(key); };
	pair<iterator, iterator> equal_range(const Key& key) { return _tree.equal_range(key); }
	pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		return _tree.equal_range(key);
	}
	iterator       lower_bound(const Key& key) { return _tree.lower_bound(key); };
	const_iterator lower_bound(const Key& key) const { return _tree.lower_bound(key); };
	iterator       upper_bound(const Key& key) { return _tree.upper_bound(key); };
	const_iterator upper_bound(const Key& key) const { return _tree.upper_bound(key); };
	/* ------------------------------- Observers ------------------------------- */
	key_compare   key_comp() const { return _key_comp; }
	value_compare value_comp() const { return _value_comp; }
};

template <class Key, class T, class Comp, class Alloc>
map<Key, T, Comp, Alloc>::map(const Comp& comp, const Alloc& alloc) :
    _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc)
{}

template <class Key, class T, class Comp, class Alloc>
template <class InputIt>
map<Key, T, Comp, Alloc>::map(InputIt first, InputIt last, const Comp& comp, const Alloc& alloc,
    typename enable_if<!is_integral<InputIt>::value>::type*) :
    _key_comp(comp),
    _value_comp(comp), _tree(_value_comp, alloc)
{
	insert(first, last);
}

template <class Key, class T, class Comp, class Alloc>
map<Key, T, Comp, Alloc>::map(map<Key, T, Comp, Alloc> const& other) :
    _key_comp(other._key_comp), _value_comp(other._value_comp), _tree(other._tree)
{}

template <class Key, class T, class Comp, class Alloc>
map<Key, T, Comp, Alloc>& map<Key, T, Comp, Alloc>::operator=(map const& other)
{
	if (this != &other) {
		_key_comp   = other._key_comp;
		_value_comp = other._value_comp;
		_tree       = other._tree;
	}
	return *this;
}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */

template <class Key, class T, class Comp, class Alloc>
T& map<Key, T, Comp, Alloc>::at(const Key& key)
{
	iterator itr = find(key);
	if (itr == end()) {
		throw std::out_of_range("map::at:  key not found");
	}
	return itr->second;
}

template <class Key, class T, class Comp, class Alloc>
const T& map<Key, T, Comp, Alloc>::at(const Key& key) const
{
	const_iterator itr = find(key);
	if (itr == end()) {
		throw std::out_of_range("map::at:  key not found");
	}
	return itr->second;
}

/* -------------------------------------------------------------------------- */
/*                            Non-member functions                            */
/* -------------------------------------------------------------------------- */
template <class Key, class T, class Compare, class Alloc>
bool operator==(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return !(lhs < rhs);
}

/* -------------------------------------------------------------------------- */
/*                                  std::swap                                 */
/* -------------------------------------------------------------------------- */
template <class Key, class T, class Compare, class Alloc>
void swap(std::map<Key, T, Compare, Alloc>& lhs, std::map<Key, T, Compare, Alloc>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft

#endif /* MAP_HPP */
