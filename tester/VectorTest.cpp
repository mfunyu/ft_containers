#include "VectorTest.hpp"
#include "Log.hpp"
#include "UnitTester.hpp"
#include <iostream>
#include <list>

t_unit_tests VectorTest::func_test_table[] = {
	{"vector_begin", vector_begin, TEST_FAILED},
	{"vector_begin", vector_begin, TEST_FAILED},
	{"vector_begin", vector_begin, TEST_FAILED},
	{"vector_begin", vector_begin, TEST_FAILED},
    {          "\0",         NULL, TEST_FAILED}
};

void VectorTest::_vector_begin_basic()
{
	Log::set_explanation("_vector_begin_basic executed");
	exit(TEST_FAILED);
	exit(TEST_SUCCESS);
}

void VectorTest::vector_begin()
{
	load_subtest_(_vector_begin_basic);
}
