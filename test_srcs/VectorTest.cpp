#include "VectorTest.hpp"
#include "Log.hpp"
#include "UnitTester.hpp"
#include <iostream>
#include <list>
#include <vector>

namespace ft = std;

namespace VectorTest {

#define FAIL TEST_FAILED

t_unit_tests func_test_table[] = {
	{        "vector_constructor",         vector_constructor, FAIL, VECTOR},
	{         "vector_destructor",          vector_destructor, FAIL, VECTOR},
	{"vector_assignment_operator", vector_assignment_operator, FAIL, VECTOR},
	{             "vector_assign",              vector_assign, FAIL, VECTOR},
	{	  "vector_get_allocator",       vector_get_allocator, FAIL, VECTOR},
	{                 "vector_at",                  vector_at, FAIL, VECTOR},
	{ "vector_subscript_operator",  vector_subscript_operator, FAIL, VECTOR},
	{              "vector_front",               vector_front, FAIL, VECTOR},
	{              "vector_begin",               vector_begin, FAIL, VECTOR},
	{               "vector_size",                vector_size, FAIL, VECTOR},
	{              "vector_empty",               vector_empty, FAIL, VECTOR},
    {                        "\0",                       NULL, FAIL, VECTOR}
};

void _set_int_array(int* array, int size = 12, bool accend = false)
{
	for (int i = 0; i < size; ++i) {
		if (accend)
			array[i] = i;
		else
			array[i] = std::rand();
	}
}

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

void _set_compare_vectors(ft::vector<int>& ft_data, std::vector<int>& std_data,
    int size = 6, bool accend = false)
{
	for (int i = 0; i < size; ++i) {
		if (accend) {
			ft_data.push_back(i);
			std_data.push_back(i);
		} else {
			int value = std::rand();
			ft_data.push_back(value);
			std_data.push_back(value);
		}
	}
}

template <class T>
void _compare_vectors(ft::vector<T>& ft_vec, std::vector<T>& std_vec)
{
	UnitTester::assert_(ft_vec.size() == std_vec.size());

	size_t size = std_vec.size();
	for (size_t i = 0; i < size; ++i) {
		UnitTester::assert_(ft_vec[i] == std_vec[i]);
	}
}

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */

void _vector_constructor_default()
{
	set_explanation_("result differs from std behavior");
	ft::vector<int>  ft;
	std::vector<int> std;
	_compare_vectors(ft, std);
}

void _vector_constructor_int()
{
	set_explanation_("result differs from std behavior");
	size_t           size  = 21;
	int              value = 42;
	ft::vector<int>  ft(size, value);
	std::vector<int> std(size, value);
	_compare_vectors(ft, std);
}

void _vector_constructor_float()
{
	set_explanation_("result differs from std behavior");
	size_t             size  = 21;
	float              value = 42.4242;
	ft::vector<float>  ft(size, value);
	std::vector<float> std(size, value);
	_compare_vectors(ft, std);
}

void _vector_constructor_string()
{
	set_explanation_("result differs from std behavior");
	size_t                   size  = 21;
	std::string              value = "42Tokyo";
	ft::vector<std::string>  ft(size, value);
	std::vector<std::string> std(size, value);
	_compare_vectors(ft, std);
}

void _vector_constructor_iterator_int()
{
	set_explanation_("result differs from std behavior");
	int  array[100];
	int* array_end = array + 100;
	_set_int_array(array, 100);

	ft::vector<int>  ft(array, array_end);
	std::vector<int> std(array, array_end);
	_compare_vectors(ft, std);
}

void _vector_constructor_iterator_vector()
{
	set_explanation_("result differs from std behavior");
	int  array[100];
	int* array_end = array + 100;
	_set_int_array(array, 100);
	std::vector<int> vec_array(array, array_end);

	std::vector<int>::iterator it     = vec_array.begin();
	std::vector<int>::iterator it_end = vec_array.end();
	ft::vector<int>            ft(it, it_end);
	std::vector<int>           std(it, it_end);
	_compare_vectors(ft, std);
}

void _vector_constructor_copy()
{
	set_explanation_("copy result differs from std behavior");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	ft::vector<int>  ft_cpy(ft);
	std::vector<int> std_cpy(std);
	_compare_vectors(ft_cpy, std_cpy);
}

void vector_constructor()
{
	load_subtest_(_vector_constructor_default);
	load_subtest_(_vector_constructor_int);
	load_subtest_(_vector_constructor_float);
	load_subtest_(_vector_constructor_string);
	load_subtest_(_vector_constructor_iterator_int);
	load_subtest_(_vector_constructor_iterator_vector);
	load_subtest_(_vector_constructor_copy);
}

/* -------------------------------------------------------------------------- */
/*                                 destructor                                 */
/* -------------------------------------------------------------------------- */

void _vector_destructor()
{
	set_explanation_("destructor cruses");
	{
		ft::vector<int> ft;
	}
}

void vector_destructor()
{
	load_subtest_(_vector_destructor);
}

/* -------------------------------------------------------------------------- */
/*                                  operator=                                 */
/* -------------------------------------------------------------------------- */

void _vector_assignemnt_operator_basic()
{
	set_explanation_("copy behavior changes original or new vector");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	ft::vector<int>  ft_copy;
	std::vector<int> std_copy;
	ft_copy  = ft;
	std_copy = std;
	_compare_vectors(ft, std);
	_compare_vectors(ft_copy, std_copy);
}

void vector_assignment_operator()
{
	load_subtest_(_vector_assignemnt_operator_basic);
}

/* -------------------------------------------------------------------------- */
/*                                   assign                                   */
/* -------------------------------------------------------------------------- */

void _vector_assign_basic()
{
	set_explanation_("value not assigned");
	ft::vector<char> ft;
	size_t           size  = 12;
	char             value = 'a';
	ft.assign(size, value);
	for (size_t i = 0; i < size; ++i)
		UnitTester::assert_(ft[i] == value);
}

void _vector_assign_overwrite()
{
	set_explanation_("value not overwritten");
	size_t          size = 7;
	ft::vector<int> ft   = _set_vector(size);

	int value = 1024;
	ft.assign(size, value);
	for (size_t i = 0; i < size; ++i)
		UnitTester::assert_(ft[i] == value);
}

void _vector_assign_compare()
{
	set_explanation_("value differs from assigned std vector");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	size_t size  = 12;
	int    value = 42;
	ft.assign(size, value);
	std.assign(size, value);
	_compare_vectors(ft, std);
}

void vector_assign()
{
	load_subtest_(_vector_assign_basic);
	load_subtest_(_vector_assign_overwrite);
	load_subtest_(_vector_assign_compare);
}

/* -------------------------------------------------------------------------- */
/*                                get_allocator                               */
/* -------------------------------------------------------------------------- */

void _vector_get_allocator_basic()
{
	set_explanation_("allocator differs from std. Really?");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	UnitTester::assert_(ft.get_allocator() == std.get_allocator());
}

void vector_get_allocator()
{
	load_subtest_(_vector_get_allocator_basic);
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
/*                                 operator[]                                 */
/* -------------------------------------------------------------------------- */

void _vector_subscript_operator_basic()
{
	set_explanation_("does not return right value. Really!?") int size = 12;
	ft::vector<int> ft_data = _set_vector(size, true);

	for (int i = 0; i < size; ++i)
		UnitTester::assert_(ft_data[i] == i);
}

void _vector_subscript_operator_compare()
{
	set_explanation_("does not return right value. Really!?") int size = 12;
	ft::vector<int>                                               ft_data;
	std::vector<int>                                              std_data;
	_set_compare_vectors(ft_data, std_data, 12);

	for (int i = 0; i < size; ++i)
		UnitTester::assert_(ft_data[i] == std_data[i]);
}

void vector_subscript_operator()
{
	load_subtest_(_vector_subscript_operator_basic);
	load_subtest_(_vector_subscript_operator_compare);
}

/* -------------------------------------------------------------------------- */
/*                                    front                                   */
/* -------------------------------------------------------------------------- */

void _vector_front_basic_int()
{
	set_explanation_("does not return the right value");
	int             size = 12;
	ft::vector<int> ft   = _set_vector(size, true);
	UnitTester::assert_(ft.front() == 1);
}

void _vector_front_basic_char()
{
	set_explanation_("does not return the right value");
	int              size  = 12;
	char             value = '*';
	ft::vector<char> ft(size, value);
	UnitTester::assert_(ft.front() == value);

	char new_value = '+';
	ft[0]          = new_value;
	UnitTester::assert_(ft.front() == new_value);
}

void _vector_front_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	UnitTester::assert_(ft.front() == std.front());
}

void vector_front()
{
	load_subtest_(_vector_front_basic_int);
	load_subtest_(_vector_front_basic_char);
	load_subtest_(_vector_front_compare);
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
