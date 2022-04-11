#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template <class Iter>
class reverse_iterator
{
  public:
	typedef Iter                                              iterator_type;
	typedef typename iterator_traits<Iter>::iterator_category iterator_category;
	typedef typename iterator_traits<Iter>::value_type        value_type;
	typedef typename iterator_traits<Iter>::difference_type   difference_type;
	typedef typename iterator_traits<Iter>::pointer           pointer;
	typedef typename iterator_traits<Iter>::reference         reference;

  protected:
	Iter current;

  public:
	// (constructor)
	reverse_iterator() : current(Iter()) {}
	explicit reverse_iterator(iterator_type x) : current(x) {}
	template <class U>
	reverse_iterator(const reverse_iterator<U>& other) : current(other.current)
	{}
	// operator=
	template <class U>
	reverse_iterator& operator=(const reverse_iterator<U>& other)
	{
		current = other.current;
		return *this;
	}
	iterator_type base() const { return current; }
	reference     operator*() const
	{
		Iter tmp = current;
		return *--tmp;
	}
	pointer operator->() const
	{
		Iter tmp = current;
		return &--tmp;
	}
	reference         operator[](difference_type n) const { return current[n]; }
	reverse_iterator& operator++()
	{
		--current;
		return *this;
	}
	reverse_iterator& operator--()
	{
		++current;
		return *this;
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator tmp(*this);
		--current;
		return tmp;
	}
	reverse_iterator operator--(int)
	{
		reverse_iterator tmp(*this);
		++current;
		return tmp;
	}
	reverse_iterator operator+(difference_type n) const
	{
		Iter tmp = current;
		tmp -= n;
		return reverse_iterator(tmp);
	}
	reverse_iterator operator-(difference_type n) const
	{
		Iter tmp = current;
		tmp += n;
		return reverse_iterator(tmp);
	}
	reverse_iterator& operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}
	reverse_iterator& operator-=(difference_type n)
	{
		current += n;
		return *this;
	}
};

/* ------------------------ Non-member functions ------------------------ */
template <class _Iter>
reverse_iterator<_Iter>
operator+(typename reverse_iterator<_Iter>::difference_type n, const reverse_iterator<_Iter>& it)
{
	reverse_iterator<_Iter> tmp = it;
	tmp.base() += n;
	return tmp;
}
template <class _Iter1, class _Iter2>
typename reverse_iterator<_Iter1>::difference_type
operator-(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}
template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}
template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() < rhs.base());
}
template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() <= rhs.base());
}
template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() > rhs.base());
}
template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

} // namespace ft

#endif /* REVERSE_ITERATOR_HPP */
