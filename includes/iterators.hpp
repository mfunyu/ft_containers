#ifndef ITERATORSHPP_
#define ITERATORSHPP_

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class T>
class random_access_iterator : public std::iterator<std::random_access_iterator_tag, T>
{
  public:
	typedef T*                                                         iterator_type;
	typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
	typedef typename iterator_traits<iterator_type>::value_type        value_type;
	typedef typename iterator_traits<iterator_type>::pointer           pointer;
	typedef typename iterator_traits<iterator_type>::reference         reference;
	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

  private:
	pointer __i;

  public:
	// (constructor)
	random_access_iterator() : __i(NULL) {}
	random_access_iterator(T* pointer) : __i(pointer) {}
	random_access_iterator(random_access_iterator const& other) : __i(other.__i) {}
	// (destructor)
	~random_access_iterator() {}

	random_access_iterator& operator=(random_access_iterator const& other)
	{
		__i = other.__i;
		return *this;
	}
	iterator_type base() const { return __i; }
	reference     operator*() const { return *__i; }
	pointer       operator->() const { return __i; }
	reference     operator[](difference_type n) const { return __i[n]; }

	/* ------------------------- Advances / Decrements ------------------------- */
	random_access_iterator& operator++()
	{
		++__i;
		return *this;
	}
	random_access_iterator& operator--()
	{
		--__i;
		return *this;
	}
	random_access_iterator operator++(int)
	{
		random_access_iterator tmp(*this);
		++__i;
		return tmp;
	}
	random_access_iterator operator--(int)
	{
		random_access_iterator tmp(*this);
		--__i;
		return tmp;
	}
	random_access_iterator& operator+(difference_type rhs)
	{
		__i += rhs;
		return *this;
	}
	random_access_iterator& operator-(difference_type rhs)
	{
		__i -= rhs;
		return *this;
	}
	random_access_iterator& operator+=(difference_type n)
	{
		__i += n;
		return *this;
	}
	random_access_iterator& operator-=(difference_type n)
	{
		__i -= n;
		return *this;
	}
};

/* -------------------------- Non-member functions ------------------------- */
template <class _Iter>
random_access_iterator<_Iter> operator+(typename random_access_iterator<_Iter>::difference_type n,
    const random_access_iterator<_Iter>&                                                        it)
{
	return random_access_iterator<_Iter>(it.base() + n);
}

template <class _Iter1, class _Iter2>
typename random_access_iterator<_Iter1>::difference_type
operator-(const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <class _Iter1, class _Iter2>
bool operator==(
    const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class _Iter1, class _Iter2>
bool operator<(const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class _Iter1, class _Iter2>
bool operator!=(
    const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return (!(lhs == rhs));
}

template <class _Iter1, class _Iter2>
bool operator<=(
    const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return (lhs < rhs || lhs == rhs);
}

template <class _Iter1, class _Iter2>
bool operator>(const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return (!(lhs < rhs) && !(lhs == rhs));
}

template <class _Iter1, class _Iter2>
bool operator>=(
    const random_access_iterator<_Iter1>& lhs, const random_access_iterator<_Iter2>& rhs)
{
	return !(lhs < rhs);
}

} // namespace ft

#endif /* ITERATORS_HPP */
