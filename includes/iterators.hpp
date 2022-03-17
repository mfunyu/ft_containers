#ifndef ITERATORSHPP_
#define ITERATORSHPP_

#include "iterator_traits.hpp"

namespace ft {

template <class T>
class random_access_iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
  public:
	typedef typename iterator_traits<T*>::difference_type   difference_type;
	typedef typename iterator_traits<T*>::value_type        value_type;
	typedef typename iterator_traits<T*>::pointer           pointer;
	typedef typename iterator_traits<T*>::reference         reference;
	typedef typename iterator_traits<T*>::iterator_category iterator_category;

  private:
	pointer __i;

  public:
	// (constructor)
	random_access_iterator() : __i(NULL) {}
	random_access_iterator(T* pointer) : __i(pointer) {}
	random_access_iterator(random_access_iterator const& other) : __i(other.__i)
	{}
	// (destructor)
	~random_access_iterator() {}

	random_access_iterator& operator=(random_access_iterator const& other)
	{
		__i = other.__i;
	}
	random_access_iterator& operator++()
	{
		++__i;
		return *this;
	}
	random_access_iterator operator++(int)
	{
		random_access_iterator tmp(T);
		++__i;
		return tmp;
	}
	random_access_iterator& operator--()
	{
		--__i;
		return *this;
	}
	random_access_iterator operator--(int)
	{
		random_access_iterator tmp(T);
		--__i;
		return tmp;
	}
	random_access_iterator& operator+() {}
	friend bool             operator==(const random_access_iterator<T>& lhs,
        const random_access_iterator<T>&                    rhs);
	friend bool             operator<(const random_access_iterator<T>& lhs,
        const random_access_iterator<T>&                   rhs);
};

template <class T>
bool operator==(
    const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
	return (lhs.__i == rhs.__i);
}
template <class T>
bool operator!=(
    const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
	return (!(lhs == rhs));
}
template <class T>
bool operator<(
    const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
	return (lhs.__i < rhs.__i);
}
template <class T>
bool operator<=(
    const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
	return (lhs < rhs || lhs == rhs);
}
template <class T>
bool operator>(
    const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
	return (!(lhs < rhs) && !(lhs == rhs));
}
template <class T>
bool operator>=(
    const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
	return !(lhs < rhs);
}

} // namespace ft

#endif /* ITERATORS_HPP */
