#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterators.hpp"
#include <iostream>
#include <memory>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector
{
  private:
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

	// (constructor)
	vector(){};
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
	allocator_type get_allocator() const {};
	// --------------------------- Elements access -------------------------- //
	// at
	reference       at(size_type pos);
	const_reference at(size_type pos) const;
	// operator[]
	reference       operator[](size_type pos){};
	const_reference operator[](size_type pos) const {};
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
	size_type size() const {};
	size_type max_size() const {};
	void      reserve(size_type new_cap){};
	size_type capacity() const {};
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
};

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator& alloc)
{}

template <class T, class Allocator>
vector<T, Allocator>::vector(
    size_type count, const T& value, const Allocator& alloc)
{}
template <class T, class Allocator>
template <class InputIt>
vector<T, Allocator>::vector(
    InputIt first, InputIt last, const Allocator& alloc)
{}
template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& other)
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
{}

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

} // namespace ft

#endif /* VECTOR_HPP */
