#include "UnitTester.hpp"
#include "TestVector.hpp"
#include <list>
#include <iostream>

t_unit_tests TestVector::func_test_table[] = {
	(t_unit_tests){"vector_begin", vector_begin},
	(t_unit_tests){"\0", NULL}
};

void TestVector::_vector_begin_basic()
{
	std::cout << "_vector_begin_basic executed" << std::endl;
}

void TestVector::vector_begin()
{
	load_subtest_(_vector_begin_basic);
}