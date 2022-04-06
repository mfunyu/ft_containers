#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

/* -------------------------------------------------------------------------- */
/*                                  enable_if                                 */
/* -------------------------------------------------------------------------- */
template <bool B, class T = void>
struct enable_if {
	typedef T type;
};

template <class T>
struct enable_if<false, T> {};



} // namespace ft

#endif /* TYPE_TRAITS_HPP */
