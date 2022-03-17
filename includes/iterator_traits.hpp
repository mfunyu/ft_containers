#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {

template <class Iterator>
class iterator_traits
{
	typedef Iterator::difference_type   difference_type;
	typedef Iterator::value_type        value_type;
	typedef Iterator::pointer           pointer;
	typedef Iterator::reference         reference;
	typedef Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*>
{
	typedef ptrdiff_t                  difference_type;
	typedef T                          value_type;
	typedef T*                         pointer;
	typedef T&                         reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	typedef ptrdiff_t                  difference_type;
	typedef T                          value_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
	typedef random_access_iterator_tag iterator_category;
};

} // namespace ft

#endif /* ITERATOR_TRAITS_HPP */
