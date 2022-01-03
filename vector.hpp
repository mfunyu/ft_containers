#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace ft {

template <class T, class Allocator = std::allocator<T>>
class vector
{
  protected:
	typedef T &								 reference;
	typedef const T &						 const_reference;
	typedef std::iterator					 iterator;
	typedef std::const_iterator				 const_iterator;
	typedef size_t							 size_type;
	typedef ptrdiff_t						 difference_type;
	typedef T								 value_type;
	typedef Allocator						 allocator_type;
	typedef Allocator::pointer				 pointer;
	typedef Allocator::const_pointer		 const_pointer;
	typedef reverse_iterator<iterator>		 reverse_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;

  public:
	/** (constructor) */
	explicit vector(const allocator_type &alloc = allocator_type()); // default
	explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type()); // fill
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
		   const allocator_type &alloc = allocator_type()); // range
	vector(const vector &x);								// copy

	/** (destructor) */
	~vector() {}
	/** operator=  */
	vector &operator=(const vector &x);

	/* Iterators: */
	iterator			   begin();
	const_iterator		   begin() const;
	iterator			   end();
	const_iterator		   end() const;
	reverse_iterator	   rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator	   rend();
	const_reverse_iterator rend() const;

	/* Capacity */
	size_type size() const;
	size_type max_size() const;
	void	  resize(size_type n, value_type val = value_type());
	size_type capacity() const;
	bool	  empty() const;
	void	  reserve(size_type n);
};
} // namespace ft

#endif /* VECTOR_HPP */