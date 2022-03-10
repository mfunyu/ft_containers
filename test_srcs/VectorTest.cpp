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
	{ "vector_size",  vector_size, TEST_FAILED, VECTOR},
	{"vector_empty", vector_empty, TEST_FAILED, VECTOR},
	{          "\0",         NULL, TEST_FAILED, VECTOR}
};

ft::vector<int> _set_vector(int size = 6, bool accend = false)
{
	ft::vector<int> data;

	for (int i = 0; i < size; ++i) {
		if (accend) {
			data.push_back(i);
		} else {
			data.push_back(std::rand());
		}
	}
	return data;
}

/* -------------------------------------------------------------------------- */
/*                                    begin                                   */
/* -------------------------------------------------------------------------- */

void _vector_begin_basic()
{
	set_explanation_("does not return the right value");
	int             size = 12;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*data.begin() == 0);
}

void _vector_begin_increment()
{
	set_explanation_("post increment returns wrong value");
	int             size = 12;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*data.begin() == 0);
	UnitTester::assert_(*++data.begin() == 1);
	UnitTester::assert_(*++(++data.begin()) == 2);
}

void _vector_begin_decrement()
{
	set_explanation_("post decrement returns wrong value");
	int             size = 12;
	ft::vector<int> data = _set_vector(size, true);

	ft::vector<int>::iterator it = data.begin() + 3;

	UnitTester::assert_(*it == 3);
	UnitTester::assert_(*--it == 2);
	UnitTester::assert_(*--it == 1);
	UnitTester::assert_(*--it == 0);
}

void vector_begin()
{
	load_subtest_(_vector_begin_basic);
	load_subtest_(_vector_begin_increment);
	load_subtest_(_vector_begin_decrement);
}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */

void _vector_at_basic()
{
	set_explanation_("does not return the right value");

	int             size = 10;
	ft::vector<int> data = _set_vector(size, true);

	for (int i = 0; i < size; ++i)
		UnitTester::assert_(data.at(i) == i);
}

void _vector_at_compare()
{
	set_explanation_("ft behaviour differs from std");

	int              size     = 20;
	ft::vector<int>  ft_data  = _set_vector(size, true);
	std::vector<int> std_data = _set_vector(size, true);

	for (int i = 0; i < size; ++i)
		UnitTester::assert_(ft_data.at(i) == std_data.at(i));
}

void _vector_at_out_of_range()
{
	set_explanation_("out of range does not throw appropriate exception");

	int             size    = 4;
	ft::vector<int> ft_data = _set_vector(size, true);

	for (int i = 0; i < size + 3; ++i) {
		try {
			ft_data.at(i);
		} catch (std::out_of_range& e) {
			UnitTester::assert_(strlen(e.what()) != 0);
		} catch (std::exception& e) {
			UnitTester::assert_(false);
		}
	}
}

void vector_at()
{
	load_subtest_(_vector_at_basic);
	load_subtest_(_vector_at_compare);
	load_subtest_(_vector_at_out_of_range);
}

/* -------------------------------------------------------------------------- */
/*                                    size                                    */
/* -------------------------------------------------------------------------- */

void _vector_size_zero()
{
	set_explanation_("wrong size returned on size 0");
	ft::vector<int> ft_data = _set_vector(0, true);
	UnitTester::assert_(ft_data.size() == 0);
}

void _vector_size_one()
{
	set_explanation_("wrong size returned on size 1");
	ft::vector<int> ft_data = _set_vector(1, true);
	UnitTester::assert_(ft_data.size() == 1);
}

void _vector_size_more()
{
	set_explanation_("wrong size returned on size more than 1");
	size_t          size    = 42;
	ft::vector<int> ft_data = _set_vector(size, true);
	UnitTester::assert_(ft_data.size() == size);
}

void vector_size()
{
	load_subtest_(_vector_size_zero);
	load_subtest_(_vector_size_one);
	load_subtest_(_vector_size_more);
}

/* -------------------------------------------------------------------------- */
/*                                    empty                                   */
/* -------------------------------------------------------------------------- */

void _vector_empty_true()
{
	set_explanation_("empty check not working. Really!?");
	ft::vector<int> ft_data = _set_vector(0, true);
	UnitTester::assert_(ft_data.empty() == true);
}

void _vector_empty_false()
{
	set_explanation_("empty check not working. Really!?");
	size_t          size    = 42;
	ft::vector<int> ft_data = _set_vector(size, true);
	UnitTester::assert_(ft_data.empty() == false);
}

void vector_empty()
{
	load_subtest_(_vector_empty_true);
	load_subtest_(_vector_empty_false);
}

} // namespace VectorTest
