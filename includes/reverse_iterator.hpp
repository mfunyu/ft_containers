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

  private:
	Iter _current;

  public:
	// (constructor)
	reverse_iterator();
	explicit reverse_iterator(iterator_type x);
	template <class U>
	reverse_iterator(const reverse_iterator<U>& other){};
	// operator=
	template <class U>
	reverse_iterator& operator=(const reverse_iterator<U>& other){};
	iterator_type     base() const {};
	reference         operator*() const {};
	pointer           operator->() const {};
	// /*unspecified*/   operator[](difference_type n) const;
	reverse_iterator& operator++(){};
	reverse_iterator& operator--(){};
	reverse_iterator  operator++(int){};
	reverse_iterator  operator--(int){};
	reverse_iterator  operator+(difference_type n) const {};
	reverse_iterator  operator-(difference_type n) const {};
	reverse_iterator& operator+=(difference_type n){};
	reverse_iterator& operator-=(difference_type n){};

	/* ------------------------ Non-member functions ------------------------ */
	template <class Iterator1, class Iterator2>
	friend bool operator==(const std::reverse_iterator<Iterator1>& lhs,
	    const std::reverse_iterator<Iterator2>&                    rhs)
	{}
	template <class Iterator1, class Iterator2>
	friend bool operator!=(const std::reverse_iterator<Iterator1>& lhs,
	    const std::reverse_iterator<Iterator2>&                    rhs)
	{}
	template <class Iterator1, class Iterator2>
	friend bool operator<(const std::reverse_iterator<Iterator1>& lhs,
	    const std::reverse_iterator<Iterator2>&                   rhs)
	{}
	template <class Iterator1, class Iterator2>
	friend bool operator<=(const std::reverse_iterator<Iterator1>& lhs,
	    const std::reverse_iterator<Iterator2>&                    rhs)
	{}
	template <class Iterator1, class Iterator2>
	friend bool operator>(const std::reverse_iterator<Iterator1>& lhs,
	    const std::reverse_iterator<Iterator2>&                   rhs)
	{}
	template <class Iterator1, class Iterator2>
	friend bool operator>=(const std::reverse_iterator<Iterator1>& lhs,
	    const std::reverse_iterator<Iterator2>&                    rhs)
	{}
};

template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>&                          it)
{}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>&       rhs)
{}
} // namespace ft

#endif /* REVERSE_ITERATOR_HPP */
