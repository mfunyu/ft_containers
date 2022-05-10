#include <iomanip>
#include <iostream>
#include <string>

#ifdef STD
#include <vector>
namespace ft = std;
#else
#include "vector.hpp"
#endif

template <typename T>
void _print_vector(const ft::vector<T>& vec)
{
	typename ft::vector<T>::const_iterator it   = vec.begin();
	typename ft::vector<T>::const_iterator it_e = vec.end();
	std::cout << "<vector>" << std::endl;
	for (; it != it_e; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/*
** Iterators
** begin	: Return iterator to beginning (public member function)
** end		: Return iterator to end (public member function)
** rbegin	: Return reverse iterator to reverse beginning (public member
** function)
** rend		: Return reverse iterator to reverse end (public member function)
*/
template <typename IteratorType>
void _test_iterators(std::string iterator_type, IteratorType iterator)
{
	IteratorType copy  = iterator;
	IteratorType copy2 = iterator;
	// IteratorType copy3 = iterator;

	std::cout << std::left << std::setw(8) << iterator_type << ": ";
	std::cout << "(--(--))" << *--(--iterator) << " ";
	std::cout << "(--)" << *--copy2 << " ";
	std::cout << *copy << " ";
	std::cout << "(++)" << *++copy << " ";
	// std::cout << "(++(++))" << *++(++copy3) << " ";
	std::cout << std::endl;
}

template <typename T>
void test_iterators(ft::vector<T> test)
{
	_print_vector(test);
	_test_iterators("begin", test.begin());
	_test_iterators("end", test.end());
	_test_iterators("rbegin", test.rbegin());
	_test_iterators("rend", test.rend());
}

void test()
{
	ft::vector<int> vector_int(7, 50);
	test_iterators<int>(vector_int);
}

int main(int ac, char** av)
{
	try {
		std::string arg = (ac > 1 ? av[1] : "");
		if (arg.empty()) {
			test();
		}
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
