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

/* -------------------------------------------------------------------------- */
/*                                 is_integral                                */
/* -------------------------------------------------------------------------- */

/* ---------------------------- integral_constant --------------------------- */
template <class T, T v>
struct integral_constant {
	static const T value = v;

	typedef T                 value_type;
	typedef integral_constant type;

	operator value_type() const { return value; }
};

/* -------------------------- true_type, false_type ------------------------- */
typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

/* ------------------------- __libcppft_is_integral ------------------------- */
/* bool, char, char16_t, char32_t, wchar_t, short, int, long, long long */
template <class T>
struct __libcppft_is_integral : public false_type {};
template <>
struct __libcppft_is_integral<bool> : public true_type {};
template <>
struct __libcppft_is_integral<char> : public true_type {};
template <>
struct __libcppft_is_integral<char16_t> : public true_type {};
template <>
struct __libcppft_is_integral<char32_t> : public true_type {};
template <>
struct __libcppft_is_integral<wchar_t> : public true_type {};
template <>
struct __libcppft_is_integral<short> : public true_type {};
template <>
struct __libcppft_is_integral<int> : public true_type {};
template <>
struct __libcppft_is_integral<long> : public true_type {};
template <>
struct __libcppft_is_integral<unsigned long> : public true_type {};

/* ------------------------------- is_integral ------------------------------ */
template <class T>
struct is_integral : public __libcppft_is_integral<typename std::remove_cv<T>::type> {};

} // namespace ft

#endif /* TYPE_TRAITS_HPP */
