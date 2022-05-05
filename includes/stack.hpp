#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack
{
  public:
	typedef Container                           container_type;
	typedef typename Container::value_type      value_type;
	typedef typename Container::size_type       size_type;
	typedef typename Container::reference       reference;
	typedef typename Container::const_reference const_reference;

	Container c;

	explicit stack(const Container& cont = Container()){};
	stack(const stack& other){};
	~stack(){};
	stack& operator=(const stack& other){};

	reference       top(){};
	const_reference top() const {};

	bool      empty() const {};
	size_type size() const {};

	void push(const value_type& value){};
	void pop(){};

	friend bool operator==(const stack& lhs, const stack& rhs){};
	friend bool operator!=(const stack& lhs, const stack& rhs){};
	friend bool operator<(const stack& lhs, const stack& rhs){};
	friend bool operator<=(const stack& lhs, const stack& rhs){};
	friend bool operator>(const stack& lhs, const stack& rhs){};
	friend bool operator>=(const stack& lhs, const stack& rhs){};
};

} // namespace ft

#endif /* STACK_HPP */
