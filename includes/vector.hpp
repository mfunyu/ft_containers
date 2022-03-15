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
};


} // namespace ft

#endif /* VECTOR_HPP */
