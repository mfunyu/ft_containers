#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterators.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector
{
  public:
	typedef T                                 value_type;
	typedef Allocator                         allocator_type;
	typedef std::size_t                       size_type;
	typedef std::ptrdiff_t                    difference_type;
	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;

	typedef random_access_iterator<T>            iterator;
	typedef random_access_iterator<T>            const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
	pointer        _begin;
	pointer        _end;
	pointer        _end_cap;
	allocator_type _alloc;

  public:
	vector() : _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(Allocator()){};
	explicit vector(const Allocator& alloc);
	explicit vector(size_type count, const T& value = T(),
	    const Allocator& alloc = Allocator());
	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
	vector(const vector& other);
	// (destructor)
	~vector(){};
	// operator=
	vector& operator=(const vector& other);
	// assign
	void assign(size_type count, const T& value);
	template <class InputIt>
	void assign(InputIt first, InputIt last);
	// get_allocator
	allocator_type get_allocator() const { return _alloc; };
	// --------------------------- Elements access -------------------------- //
	// at
	reference       at(size_type pos);
	const_reference at(size_type pos) const;
	// operator[]
	reference       operator[](size_type pos) { return _begin[pos]; };
	const_reference operator[](size_type pos) const { return _begin[pos]; };
	// front
	reference       front(){};
	const_reference front() const {};
	// back
	reference       back(){};
	const_reference back() const {};
	// data
	T*       data(){};
	const T* data() const {};
	// ------------------------------ Iterators ----------------------------- //
	iterator               begin(){};
	const_iterator         begin() const {};
	iterator               end(){};
	const_iterator         end() const {};
	reverse_iterator       rbegin(){};
	const_reverse_iterator rbegin() const {};
	reverse_iterator       rend(){};
	const_reverse_iterator rend() const {};
	// ------------------------------ Capacity ------------------------------ //
	bool      empty() const {};
	size_type size() const { return static_cast<size_type>(_end - _begin); };
	size_type max_size() const
	{
		return std::numeric_limits<difference_type>::max();
	};
	void      reserve(size_type new_cap);
	size_type capacity() const
	{
		return static_cast<size_type>(_end_cap - _begin);
	};
	/* ------------------------------ Modifiers ----------------------------- */
	void clear(){};
	// insert
	iterator insert(iterator pos, const T& value);
	void     insert(iterator pos, size_type count, const T& value);
	template <class InputIt>
	void insert(iterator pos, InputIt first, InputIt last);
	// erase
	iterator erase(iterator pos){};
	iterator erase(iterator first, iterator last){};
	// push_back
	void push_back(const T& value){};
	void pop_back(){};
	void resize(size_type count, T value = T()){};
	void swap(vector& other){};

  private:
	void _vallocate(size_type n);
};

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator& alloc) :
    _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
{}

template <class T, class Allocator>
vector<T, Allocator>::vector(
    size_type count, const T& value, const Allocator& alloc) :
    _begin(NULL),
    _end(NULL), _end_cap(NULL), _alloc(alloc)
{
	assign(count, value);
}

template <class T, class Allocator>
template <class InputIt>
vector<T, Allocator>::vector(
    InputIt first, InputIt last, const Allocator& alloc) :
    _begin(NULL),
    _end(NULL), _end_cap(NULL), _alloc(alloc)
{}
template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& other) : _alloc(other._alloc)
{}

/* -------------------------------------------------------------------------- */
/*                                  operator=                                 */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>&
vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
{}

/* -------------------------------------------------------------------------- */
/*                                   assign                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::assign(size_type count, const T& value)
{
	pointer current;

	if (capacity() < count)
		reserve(count);
	current = _begin;
	for (size_type i = 0; i < count; ++i, ++current) {
		*current = value;
	}
	_end += count;
}

template <class T, class Allocator>
template <class InputIt>
void vector<T, Allocator>::assign(InputIt first, InputIt last)
{}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos)
{}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at(size_type pos) const
{}

/* -------------------------------------------------------------------------- */
/*                                   reserve                                  */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::reserve(size_type new_cap)
{
	if (capacity() > new_cap)
		return;
	size_type _size     = size();
	pointer   new_begin = _alloc.allocate(new_cap);
	std::uninitialized_copy(_begin, _end, new_begin);
	_alloc.destroy(_begin);

	_begin   = new_begin;
	_end     = _begin + _size;
	_end_cap = _begin + new_cap;
}

/* -------------------------------------------------------------------------- */
/*                                   insert                                   */
/* -------------------------------------------------------------------------- */
// /*
template <class T, class Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(iterator pos, const T& value)
{}

template <class T, class Allocator>
void vector<T, Allocator>::insert(iterator pos, size_type count, const T& value)
{}

template <class T, class Allocator>
template <class InputIt>
void vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
{}
// */

/* -------------------------------------------------------------------------- */
/*                            Non-member functions                            */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{}
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{}

/* -------------------------------------------------------------------------- */
/*                                  std::swap                                 */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
void swap(std::vector<T, Alloc>& lhs, std::vector<T, Alloc>& rhs)
{}

/* -------------------------------------------------------------------------- */
/*                          private member functions                          */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
void vector<T, Alloc>::_vallocate(size_type n)
{
	if (n > max_size())
		throw std::logic_error("allocation size too large");
	_begin   = _alloc.allocate(n);
	_begin   = _end;
	_end_cap = _begin + n;
}

} // namespace ft

#endif /* VECTOR_HPP */
