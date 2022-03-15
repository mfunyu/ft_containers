#ifndef VECTOR_HPP
#define VECTOR_HPP

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

	/*
	typedef iterator;
	typedef const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	*/

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

	size_t    size() { return 0; };
	void      push_back(T t) { (void)t; };
	reference operator[](size_type pos){};
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

} // namespace ft

#endif /* VECTOR_HPP */
