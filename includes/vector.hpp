#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
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
	explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());
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
	reference       front() { return *_begin; };
	const_reference front() const { return *_begin; };
	// back
	reference       back() { return *(_end - 1); };
	const_reference back() const { return *(_end - 1); };
	// data
	T*       data() { return static_cast<T*>(_begin); };
	const T* data() const { return static_cast<const T*>(_begin); };
	// ------------------------------ Iterators ----------------------------- //
	iterator               begin() { return iterator(_begin); };
	const_iterator         begin() const { return const_iterator(_begin); };
	iterator               end() { return iterator(_end); };
	const_iterator         end() const { return const_iterator(_end); };
	reverse_iterator       rbegin() { return reverse_iterator(end()); };
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
	reverse_iterator       rend() { return reverse_iterator(begin()); };
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };
	// ------------------------------ Capacity ------------------------------ //
	bool      empty() const { return (size() == 0); };
	size_type size() const { return static_cast<size_type>(_end - _begin); };
	size_type max_size() const { return std::numeric_limits<difference_type>::max(); };
	void      reserve(size_type new_cap);
	size_type capacity() const { return static_cast<size_type>(_end_cap - _begin); };
	/* ------------------------------ Modifiers ----------------------------- */
	void clear();
	// insert
	iterator insert(iterator pos, const T& value);
	void     insert(iterator pos, size_type count, const T& value);
	template <class InputIt>
	void insert(iterator pos, InputIt first, InputIt last);
	// erase
	iterator erase(iterator pos){};
	iterator erase(iterator first, iterator last){};
	// push_back
	void push_back(const T& value);
	void pop_back();
	void resize(size_type count, T value = T()){};
	void swap(vector& other){};

  private:
	void _vallocate(size_type n);
	void _construct_at_end(size_type n);
	void _destruct_at_end(pointer new_last);
};

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator& alloc) :
    _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
{}

template <class T, class Allocator>
vector<T, Allocator>::vector(size_type count, const T& value, const Allocator& alloc) :
    _alloc(alloc)
{
	_vallocate(count);
	assign(count, value);
}

template <class T, class Allocator>
template <class InputIt>
vector<T, Allocator>::vector(InputIt first, InputIt last, const Allocator& alloc) : _alloc(alloc)
{
	size_type count = static_cast<size_type>(last - first);
	_vallocate(count);
	std::uninitialized_copy(first, last, _begin);
	_end = _begin + count;
}

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& other) : _alloc(other._alloc)
{
	size_type count = other.size();

	_vallocate(count);
	std::uninitialized_copy(other._begin, other._end, _begin);
	_end = _begin + count;
}

/* -------------------------------------------------------------------------- */
/*                                  operator=                                 */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
{
	if (this != &other) {
		size_type count = other.size();
		_vallocate(count);
		std::uninitialized_copy(other._begin, other._end, _begin);
		_end = _begin + count;
	}
	return *this;
}

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
	_end = _begin + count;
}

template <class T, class Allocator>
template <class InputIt>
void vector<T, Allocator>::assign(InputIt first, InputIt last)
{
	size_type count = static_cast<size_type>(last - first);
	pointer   current;

	if (capacity() < count)
		reserve(count);
	current = _begin;
	for (InputIt it = first; it != last; ++it, ++current) {
		*current = *it;
	}
	_end = _begin + count;
}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos)
{
	if (pos >= size())
		throw std::out_of_range("index out of range");
	return _begin[pos];
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const
{
	if (pos >= size())
		throw std::out_of_range("index out of range");
	return _begin[pos];
}

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
/*                                    clear                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::clear()
{
	for (pointer ptr = _begin; ptr == _end; ++ptr) {
		_alloc.destroy(ptr);
	}
	_begin = _end;
}

/* -------------------------------------------------------------------------- */
/*                                   insert                                   */
/* -------------------------------------------------------------------------- */
// /*
template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const T& value)
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
/*                                  push_back                                 */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::push_back(const T& value)
{
	size_type new_size = size() + 1;
	if (capacity() < new_size)
		reserve(new_size);
	_begin[new_size - 1] = value;
	_end++;
}

/* -------------------------------------------------------------------------- */
/*                                  pop_back                                  */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::pop_back()
{
	_destruct_at_end(_end - 1);
}

/* -------------------------------------------------------------------------- */
/*                            Non-member functions                            */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lhs == rhs || lhs < rhs);
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs < rhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lhs == rhs || lhs > rhs);
}

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
	_end     = _begin;
	_end_cap = _begin + n;
}

template <class T, class Alloc>
void vector<T, Alloc>::_construct_at_end(size_type n)
{
	while (n > 0) {
		_alloc.construct(_end);
		++_end;
		--n;
	}
}

template <class T, class Alloc>
void vector<T, Alloc>::_destruct_at_end(pointer new_last)
{
	while (_end != new_last) {
		--_end;
		_alloc.destroy(_end);
	}
}

} // namespace ft

#endif /* VECTOR_HPP */
