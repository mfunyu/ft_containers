#include "UnitTester.hpp"
#include "test_vector.hpp"
#include <list>
#include <iostream>

namespace test_vector {

t_unit_tests func_test_table[] = {
	(t_unit_tests){"vector_begin", vector_begin}
};

void _vector_begin_basic()
{
	std::cout << "subtest" << std::endl;
}

void vector_begin()
{
	load_subtest_(_vector_begin_basic);
}

} // namespace test_vector
