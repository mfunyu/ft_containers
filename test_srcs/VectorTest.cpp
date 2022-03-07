#include "VectorTest.hpp"
#include "Log.hpp"
#include "UnitTester.hpp"
#include <iostream>
#include <list>
#include <vector>

namespace ft = std;

namespace VectorTest {

t_unit_tests func_test_table[] = {
	{"vector_begin", vector_begin, TEST_FAILED, VECTOR},
	{   "vector_at",    vector_at, TEST_FAILED, VECTOR},
    {          "\0",         NULL, TEST_FAILED, VECTOR}
};

/* -------------------------------------------------------------------------- */
/*                                    begin                                   */
/* -------------------------------------------------------------------------- */

void _vector_begin_basic()
{
	Log::set_explanation("_vector_begin_basic executed");
	exit(TEST_FAILED);
	exit(TEST_SUCCESS);
}

void vector_begin()
{
	load_subtest_(_vector_begin_basic);
}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */

void _vector_at_basic()
{
	ft::vector<int> data;
	for (int i = 0; i <= 5; ++i)
		data.push_back(i);
	for (int i = 0; i <= 5; ++i)
		UnitTester::assert_(data.at(i) == i);
}

void _vector_at_compare() {}

void vector_at()
{
	load_subtest_(_vector_at_basic);
	load_subtest_(_vector_at_compare);
}

}
