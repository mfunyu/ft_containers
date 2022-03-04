#include "VectorTest.hpp"
#include "UnitTester.hpp"
#include <iostream>
#include <list>

t_unit_tests VectorTest::func_test_table[] = {
	{"vector_begin", vector_begin},
    {"vector_begin", vector_begin},
	{"vector_begin", vector_begin},
    {"vector_begin", vector_begin},
	{          "\0",         NULL}
};

void VectorTest::_vector_begin_basic()
{
	std::cout << "_vector_begin_basic executed" << std::endl;
	exit(TEST_SUCCESS);
	exit(TEST_FAILED);
}

void VectorTest::vector_begin()
{
	load_subtest_(_vector_begin_basic);
}
