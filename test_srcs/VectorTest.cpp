#include "VectorTest.hpp"
#include "Log.hpp"
#include "UnitTester.hpp"
#include <algorithm>
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
 // --------------------------- Element access --------------------------- //
	{                 "vector_at",                  vector_at, FAIL, VECTOR},
	{ "vector_subscript_operator",  vector_subscript_operator, FAIL, VECTOR},
	{              "vector_front",               vector_front, FAIL, VECTOR},
	{               "vector_back",                vector_back, FAIL, VECTOR},
	{               "vector_data",                vector_data, FAIL, VECTOR},
 // ------------------------------ Iterators ----------------------------- //
	{              "vector_begin",               vector_begin, FAIL, VECTOR},
	{                "vector_end",                 vector_end, FAIL, VECTOR},
	{             "vector_rbegin",              vector_rbegin, FAIL, VECTOR},
	{               "vector_rend",                vector_rend, FAIL, VECTOR},
 // ------------------------------ Capacity ----------------------------- //
	{              "vector_empty",               vector_empty, FAIL, VECTOR},
	{               "vector_size",                vector_size, FAIL, VECTOR},
	{           "vector_max_size",            vector_max_size, FAIL, VECTOR},
	{            "vector_reserve",             vector_reserve, FAIL, VECTOR},
	{           "vector_capacity",            vector_capacity, FAIL, VECTOR},
 // ------------------------------ Modifiers ----------------------------- //
	{              "vector_clear",               vector_clear, FAIL, VECTOR},
	{             "vector_insert",              vector_insert, FAIL, VECTOR},
	{              "vector_erase",               vector_erase, FAIL, VECTOR},
	{          "vector_push_back",           vector_push_back, FAIL, VECTOR},
	{           "vector_pop_back",            vector_pop_back, FAIL, VECTOR},
	{             "vector_resize",              vector_resize, FAIL, VECTOR},
	{               "vector_swap",                vector_swap, FAIL, VECTOR},
 // ------------------------ Non-member functions ------------------------ //
	{         "vector_operator_e",          vector_operator_e, FAIL, VECTOR},
	{        "vector_operator_ne",         vector_operator_ne, FAIL, VECTOR},
	{         "vector_operator_l",          vector_operator_l, FAIL, VECTOR},
	{        "vector_operator_le",         vector_operator_le, FAIL, VECTOR},
	{         "vector_operator_g",          vector_operator_g, FAIL, VECTOR},
	{        "vector_operator_ge",         vector_operator_ge, FAIL, VECTOR},
	{           "vector_std_swap",            vector_std_swap, FAIL, VECTOR},
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

ft::vector<char> _set_vector_char(size_t size = 6, bool accend = false)
{
	ft::vector<char> data;
	char             val;

	for (size_t i = 0; i < size; ++i) {

		if (accend) {
			val = 'a' + i;
		} else
			val = 'a' + std::rand() % 26;
		data.push_back(val);
	}
	return data;
}

ft::vector<std::string> _set_vector_string(size_t size = 6, bool random = false)
{
	ft::vector<std::string> data;
	std::string             strs[]   = { "42", "Tokyo", "Hello", "World", "!" };
	size_t                  patterns = 5;
	std::string             val;
	int                     index;

	for (size_t i = 0; i < size; ++i) {
		if (random)
			index = std::rand() % patterns;
		else
			index = i % patterns;
		val = strs[index] + strs[std::max(index - 1, 0)];
		data.push_back(val);
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

template <class T>
void _debug(ft::vector<T>& ft_vec, std::string name = "")
{
	std::cerr << std::endl;
	std::cerr << "[" << name << "] ";
	size_t size = ft_vec.size();
	for (size_t i = 0; i < size; ++i) {
		std::cerr << i << ": " << ft_vec[i] << " ";
	}
	std::cerr << std::endl;
}

// -------------------------------------------------------------------------- //
//                                 constructor                                //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                 destructor                                 //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                  operator=                                 //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                   assign                                   //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                get_allocator                               //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                     at                                     //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                 operator[]                                 //
// -------------------------------------------------------------------------- //

void _vector_subscript_operator_basic()
{
	set_explanation_("does not return right value. Really!?");
	int             size    = 12;
	ft::vector<int> ft_data = _set_vector(size, true);

	for (int i = 0; i < size; ++i)
		UnitTester::assert_(ft_data[i] == i);
}

void _vector_subscript_operator_compare()
{
	set_explanation_("does not return right value. Really!?");
	int              size = 12;
	ft::vector<int>  ft_data;
	std::vector<int> std_data;
	_set_compare_vectors(ft_data, std_data, 12);

	for (int i = 0; i < size; ++i)
		UnitTester::assert_(ft_data[i] == std_data[i]);
}

void vector_subscript_operator()
{
	load_subtest_(_vector_subscript_operator_basic);
	load_subtest_(_vector_subscript_operator_compare);
}

// -------------------------------------------------------------------------- //
//                                    front                                   //
// -------------------------------------------------------------------------- //

void _vector_front_basic_int()
{
	set_explanation_("does not return the right value");
	int             size = 12;
	ft::vector<int> ft   = _set_vector(size, true);
	UnitTester::assert_(ft.front() == 0);
}

void _vector_front_basic_char()
{
	int              size  = 12;
	char             value = '*';
	ft::vector<char> ft(size, value);
	set_explanation_("does not return the right value");
	UnitTester::assert_(ft.front() == value);

	char new_value = '+';
	ft[0]          = new_value;
	set_explanation_("does not return the updated value");
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

// -------------------------------------------------------------------------- //
//                                    back                                    //
// -------------------------------------------------------------------------- //

void _vector_back_basic_int()
{
	set_explanation_("does not return the right value");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);
	UnitTester::assert_(ft.back() == size - 1);
}

void _vector_back_basic_char()
{
	int              size  = 10;
	char             value = '*';
	ft::vector<char> ft(size, value);
	set_explanation_("does not return the right value");
	UnitTester::assert_(ft.back() == value);

	char new_value = '+';
	ft[size - 1]   = new_value;
	set_explanation_("does not return the updated value");
	UnitTester::assert_(ft.back() == new_value);
}

void _vector_back_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	UnitTester::assert_(ft.back() == std.back());
}

void vector_back()
{
	load_subtest_(_vector_back_basic_int);
	load_subtest_(_vector_back_basic_char);
	load_subtest_(_vector_back_compare);
}

// -------------------------------------------------------------------------- //
//                                    data                                    //
// -------------------------------------------------------------------------- //

void _vector_data_basic()
{
	set_explanation_("does not return the right value");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	UnitTester::assert_(*ft.data() == 0);
}

void _vector_data_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	UnitTester::assert_(*ft.data() == *std.data());
}

void vector_data()
{
	load_subtest_(_vector_data_basic);
	load_subtest_(_vector_data_compare);
}

// -------------------------------------------------------------------------- //
//                                    begin                                   //
// -------------------------------------------------------------------------- //

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
}

// -------------------------------------------------------------------------- //
//                                    end                                   //
// -------------------------------------------------------------------------- //

void _vector_end_basic()
{
	set_explanation_("does not return the right value");
	int             size = 7;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*--data.end() == size - 1);
}

void _vector_end_increment()
{
	set_explanation_("post increment returns wrong value");
	int             size = 9;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*--data.end() == size - 1);
	UnitTester::assert_(*--(--data.end()) == size - 2);
	UnitTester::assert_(*--(--(--data.end())) == size - 3);
}

void vector_end()
{
	load_subtest_(_vector_end_basic);
	load_subtest_(_vector_end_increment);
}

// -------------------------------------------------------------------------- //
//                                    rbegin                                  //
// -------------------------------------------------------------------------- //

void _vector_rbegin_basic()
{
	set_explanation_("does not return the right value");
	int             size = 12;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*data.rbegin() == size - 1);
}

void _vector_rbegin_increment()
{
	set_explanation_("post increment returns wrong value");
	int             size = 12;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*data.rbegin() == size - 1);
	UnitTester::assert_(*++data.rbegin() == size - 2);
	UnitTester::assert_(*++(++data.rbegin()) == size - 3);
}

void vector_rbegin()
{
	load_subtest_(_vector_rbegin_basic);
	load_subtest_(_vector_rbegin_increment);
}

// -------------------------------------------------------------------------- //
//                                    rend                                    //
// -------------------------------------------------------------------------- //

void _vector_rend_basic()
{
	set_explanation_("does not return the right value");
	int             size = 7;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*--data.rend() == 0);
}

void _vector_rend_increment()
{
	set_explanation_("post increment returns wrong value");
	int             size = 9;
	ft::vector<int> data = _set_vector(size, true);

	UnitTester::assert_(*--data.rend() == 0);
	UnitTester::assert_(*--(--data.rend()) == 1);
	UnitTester::assert_(*--(--(--data.rend())) == 2);
}

void vector_rend()
{
	load_subtest_(_vector_rend_basic);
	load_subtest_(_vector_rend_increment);
}

// -------------------------------------------------------------------------- //
//                                    empty                                   //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                    size                                    //
// -------------------------------------------------------------------------- //

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

// -------------------------------------------------------------------------- //
//                                  max_size                                  //
// -------------------------------------------------------------------------- //

void _vector_max_size_multiple()
{
	set_explanation_("multiple vectors does not return the same max value");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size);
	ft::vector<int> ft2  = _set_vector(size + 100);

	UnitTester::assert_(ft.max_size() == ft2.max_size());
}

void _vector_max_size_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	UnitTester::assert_(ft.max_size() == std.max_size());
}

void vector_max_size()
{
	load_subtest_(_vector_max_size_multiple);
	load_subtest_(_vector_max_size_compare);
}

// -------------------------------------------------------------------------- //
//                                   reserve                                  //
// -------------------------------------------------------------------------- //

void _vector_reserve_basic()
{
	set_explanation_("faied to reserve normal size capacity");
	unsigned int    new_capacity = 42;
	int             size         = 2;
	ft::vector<int> ft           = _set_vector(size);
	ft.reserve(new_capacity);

	UnitTester::assert_(ft.capacity() == new_capacity);
}

void _vector_reserve_large()
{
	set_explanation_("faied to reserve large capacity");
	unsigned int    new_capacity = INT_MAX;
	int             size         = 2;
	ft::vector<int> ft           = _set_vector(size);
	ft.reserve(new_capacity);

	UnitTester::assert_(ft.capacity() == new_capacity);
}

void _vector_reserve_extra_large()
{
	set_explanation_("faied to reserve extra large capacity");
	size_t          new_capacity = SIZE_MAX;
	int             size         = 2;
	ft::vector<int> ft           = _set_vector(size);

	try {
		ft.reserve(new_capacity);
	} catch (std::length_error& e) {
		exit(TEST_SUCCESS);
	} catch (std::exception& e) {
		set_explanation_("exception not thrown from allocator");
	}
	UnitTester::assert_(ft.capacity() == new_capacity);
}

void _vector_reserve_compare()
{
	set_explanation_("result differs from std");
	unsigned int     new_capacity = 121;
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);
	ft.reserve(new_capacity);
	std.reserve(new_capacity);

	UnitTester::assert_(ft.capacity() == std.capacity());
}

void vector_reserve()
{
	load_subtest_(_vector_reserve_basic);
	load_subtest_(_vector_reserve_large);
	load_subtest_(_vector_reserve_extra_large);
	load_subtest_(_vector_reserve_compare);
}

// -------------------------------------------------------------------------- //
//                                  capacity                                  //
// -------------------------------------------------------------------------- //

void _vector_capacity_ratio()
{
	set_explanation_("capacity not 0 at size 0");
	ft::vector<int> ft;
	size_t          cap = ft.capacity();
	UnitTester::assert_(cap == 0);

	size_t size = 4242;
	for (size_t i = 0; i < size; ++i) {
		if (cap != ft.capacity()) {
			if (i == 1) {
				cap = ft.capacity();
				set_explanation_("capacity is not 1 at size 1");
				UnitTester::assert_(cap == 1);
				continue;
			}
			set_explanation_("capacity is not doubled the size");
			UnitTester::assert_(ft.capacity() / static_cast<float>(cap) == 2);
			cap = ft.capacity();
		}
		ft.push_back(i);
	}
}

void _vector_capacity_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);

	UnitTester::assert_(ft.capacity() == std.capacity());
}

void vector_capacity()
{
	load_subtest_(_vector_capacity_ratio);
	load_subtest_(_vector_capacity_compare);
}

// -------------------------------------------------------------------------- //
//                                    clear                                   //
// -------------------------------------------------------------------------- //

void _vector_clear_size_check()
{
	set_explanation_("size not 0");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size);

	UnitTester::assert_(ft.size() != 0);
	ft.clear();
	UnitTester::assert_(ft.size() == 0);
}

void _vector_clear_capacity_check()
{
	set_explanation_("capacity modified to 0");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size);

	UnitTester::assert_(ft.capacity() != 0);
	ft.clear();
	UnitTester::assert_(ft.capacity() != 0);
}

void _vector_clear_empty_check()
{
	set_explanation_("is empty not true");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	UnitTester::assert_(!ft.empty());
	ft.clear();
	UnitTester::assert_(ft.empty());
}

void vector_clear()
{
	load_subtest_(_vector_clear_size_check);
	load_subtest_(_vector_clear_capacity_check);
	load_subtest_(_vector_clear_empty_check);
}

// -------------------------------------------------------------------------- //
//                                   insert                                   //
// -------------------------------------------------------------------------- //

void _vector_insert_single()
{
	set_explanation_("value not inserted at expected point");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size);

	ft::vector<int>::iterator it    = ft.begin();
	int                       value = 42;
	ft.insert(it, value);
	UnitTester::assert_(ft[0] == value);
}

void _vector_insert_double()
{
	set_explanation_("value not inserted at expected point");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size);

	ft::vector<int>::iterator it    = ft.begin();
	int                       value = 42;
	ft.insert(it, 2, value);
	UnitTester::assert_(ft[0] == value);
	UnitTester::assert_(ft[1] == value);
}

void _vector_insert_multiple()
{
	set_explanation_("value not inserted at expected point");
	int                     size = 10;
	ft::vector<std::string> ft   = _set_vector_string(size);

	ft::vector<std::string>::iterator it    = ft.begin();
	std::string                       value = "Vector Test";
	size_t                            count = 5;

	ft.insert(it, 5, value);
	for (size_t i = 0; i < count; ++i) {
		UnitTester::assert_(ft[i] == value);
	}
}

void _vector_insert_iterator()
{
	set_explanation_("value not inserted at expected point");
	size_t           size  = 12;
	char             value = 'x';
	ft::vector<char> ft_src(size, value);

	ft::vector<char> ft = _set_vector_char(size, true);

	ft::vector<char>::iterator it = ft.begin() + 2;
	ft.insert(it, ft_src.begin(), ft_src.end());

	// `it` no longer valid, get a new one:
	it = ft.begin() + 2;
	for (size_t i = 0; it != ft.end() && i < size; ++it, ++i) {
		UnitTester::assert_(*it == value);
	}
}

void _vector_insert_compare()
{
	set_explanation_("result differs from std");
	size_t           src_size = 22;
	ft::vector<int>  ft_src;
	std::vector<int> std_src;
	_set_compare_vectors(ft_src, std_src, src_size);

	size_t           size = 57;
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std, size);

	// insert_point < size
	int insert_point = 13;
	ft.insert(ft.begin() + insert_point, ft_src.begin(), ft_src.end());
	std.insert(std.begin() + insert_point, std_src.begin(), std_src.end());
	_compare_vectors(ft, std);
}

void vector_insert()
{
	load_subtest_(_vector_insert_single);
	load_subtest_(_vector_insert_double);
	load_subtest_(_vector_insert_multiple);
	load_subtest_(_vector_insert_iterator);
	load_subtest_(_vector_insert_compare);
}
// -------------------------------------------------------------------------- //
//                                    erase                                   //
// -------------------------------------------------------------------------- //

void _vector_erase_one()
{
	set_explanation_("an element not erased");
	size_t          size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	ft.erase(ft.begin() + 3);
	UnitTester::assert_(ft.size() == size - 1);
}

void _vector_erase_head()
{
	set_explanation_("the first element not erased");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	ft.erase(ft.begin());
	UnitTester::assert_(ft[0] == 1);
}

void _vector_erase_tail()
{
	set_explanation_("the last element not erased");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	ft.erase(--ft.end());
	size = ft.size();
	UnitTester::assert_(ft[size - 1] == size - 1);
}

void _vector_erase_range()
{
	set_explanation_("elements in range not erased");
	int             size = 21;
	ft::vector<int> ft   = _set_vector(size, true);

	// erase_len < size
	int erase_len = 5;
	ft.erase(ft.begin(), ft.begin() + erase_len);
	UnitTester::assert_(ft[0] == erase_len);
}

void _vector_erase_compare()
{
	set_explanation_("result differs from std");
	int              size = 42;
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std, size);

	size_t                     start_position = 2;
	ft::vector<int>::iterator  ft_start       = ft.begin() + start_position;
	std::vector<int>::iterator std_start      = std.begin() + start_position;

	size_t len = 15;
	ft.erase(ft_start, ft_start + len);
	std.erase(std_start, std_start + len);
	_compare_vectors(ft, std);
}

void vector_erase()
{
	load_subtest_(_vector_erase_one);
	load_subtest_(_vector_erase_head);
	load_subtest_(_vector_erase_tail);
	load_subtest_(_vector_erase_range);
	load_subtest_(_vector_erase_compare);
}

// -------------------------------------------------------------------------- //
//                                  push_back                                 //
// -------------------------------------------------------------------------- //

void _vector_push_back_empty()
{
	set_explanation_("added value not correct");
	ft::vector<int> ft;

	int value = 42;
	ft.push_back(value);
	UnitTester::assert_(ft[0] == value);
}

void _vector_push_back_one()
{
	set_explanation_("added value not correct");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	int value = 42;
	ft.push_back(value);
	UnitTester::assert_(ft[size] == value);
}

void _vector_push_back_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std);
	_compare_vectors(ft, std);
}

void vector_push_back()
{
	load_subtest_(_vector_push_back_empty);
	load_subtest_(_vector_push_back_one);
	load_subtest_(_vector_push_back_compare);
}

// -------------------------------------------------------------------------- //
//                                  pop_back                                  //
// -------------------------------------------------------------------------- //

void _vector_pop_back_empty()
{
	set_explanation_("size not reduced as expected");
	ft::vector<int> ft;
	ft.pop_back();

	UnitTester::assert_(ft.size() == static_cast<size_t>(-1));
}

void _vector_pop_back_one()
{
	set_explanation_("size not reduced");
	size_t          size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	ft.pop_back();
	UnitTester::assert_(ft.size() == size - 1);
}

void _vector_pop_back_compare_zero()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft;
	std::vector<int> std;

	ft.pop_back();
	std.pop_back();
	UnitTester::assert_(ft.size() == std.size());
}

void _vector_pop_back_compare()
{
	set_explanation_("result differs from std");
	size_t           size = 16;
	ft::vector<int>  ft;
	std::vector<int> std;
	_set_compare_vectors(ft, std, size);

	for (size_t i = 0; i < size; ++i) {
		ft.pop_back();
		std.pop_back();
		_compare_vectors(ft, std);
	}
}

void vector_pop_back()
{
	load_subtest_(_vector_pop_back_empty);
	load_subtest_(_vector_pop_back_one);
	load_subtest_(_vector_pop_back_compare_zero);
	load_subtest_(_vector_pop_back_compare);
}

// -------------------------------------------------------------------------- //
//                                   resize                                   //
// -------------------------------------------------------------------------- //

void _vector_resize_expand()
{
	set_explanation_("size not expanded or initialized");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	size_t new_size = 19;
	ft.resize(new_size);
	UnitTester::assert_(ft.size() == new_size);
	UnitTester::assert_(ft[new_size - 1] == 0);
}

void _vector_resize_reduce()
{
	set_explanation_("size not reduced");
	int             size = 7;
	ft::vector<int> ft   = _set_vector(size, true);

	size_t new_size = 2;
	ft.resize(new_size);
	UnitTester::assert_(ft.size() == new_size);
}

void _vector_resize_same()
{
	set_explanation_("size changed");
	int             size = 5;
	ft::vector<int> ft   = _set_vector(size, true);

	size_t new_size = size;
	ft.resize(new_size);
	UnitTester::assert_(ft.size() == new_size);
}

void _vector_resize_initializer()
{
	set_explanation_("initializer not applied");
	int             size = 8;
	ft::vector<int> ft   = _set_vector(size, true);

	size_t new_size    = 24;
	int    initializer = 4242;
	ft.resize(new_size, initializer);
	for (size_t i = size; i < new_size; ++i) {
		UnitTester::assert_(ft[i] == initializer);
	}
}

void vector_resize()
{
	load_subtest_(_vector_resize_expand);
	load_subtest_(_vector_resize_reduce);
	load_subtest_(_vector_resize_same);
	load_subtest_(_vector_resize_initializer);
}

// -------------------------------------------------------------------------- //
//                                    swap                                    //
// -------------------------------------------------------------------------- //

void _vector_swap_basic()
{
	set_explanation_("swapped value not correct");
	size_t          size_a = 10;
	size_t          size_b = 20;
	ft::vector<int> ft_a   = _set_vector(size_a, false);
	ft::vector<int> ft_b   = _set_vector(size_b, true);

	ft_a.swap(ft_b);
	for (size_t i = 0; i < size_b; ++i) {
		ft_a[i] = i;
	}
}

void _vector_swap_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft_a;
	std::vector<int> std_a;
	_set_compare_vectors(ft_a, std_a);

	ft::vector<int>  ft_b;
	std::vector<int> std_b;
	_set_compare_vectors(ft_b, std_b);

	ft_a.swap(ft_b);
	std_a.swap(std_b);
	_compare_vectors(ft_a, std_a);
	_compare_vectors(ft_b, std_b);
}

void _vector_swap_iterator()
{
	set_explanation_("iterator is invalidated");
	ft::vector<int>           ft_a    = _set_vector();
	ft::vector<int>           ft_b    = _set_vector();
	ft::vector<int>::iterator it_a    = ft_a.begin();
	ft::vector<int>::iterator it_b    = ft_b.begin();
	int                       value_a = ft_a[0];
	int                       value_b = ft_b[0];

	UnitTester::assert_(*it_a == value_a);
	UnitTester::assert_(*it_b == value_b);
	ft_a.swap(ft_b);
	UnitTester::assert_(*it_a == value_a);
	UnitTester::assert_(*it_b == value_b);
	UnitTester::assert_(*ft_a.begin() == value_b);
	UnitTester::assert_(*ft_b.begin() == value_a);
}

void vector_swap()
{
	load_subtest_(_vector_swap_basic);
	load_subtest_(_vector_swap_compare);
	load_subtest_(_vector_swap_iterator);
}

// -------------------------------------------------------------------------- //
//                                 operator==                                 //
// -------------------------------------------------------------------------- //

void _vector_operator_e_true()
{
	set_explanation_("wrong result on value int");
	int             size_1 = 10;
	int             size_2 = size_1;
	ft::vector<int> ft_1   = _set_vector(size_1, true);
	ft::vector<int> ft_2   = _set_vector(size_2, true);

	UnitTester::assert_((ft_1 == ft_2) == true);
}

void _vector_operator_e_true_empty()
{
	set_explanation_("empty vectors are not equal");
	ft::vector<int> ft_1;
	ft::vector<int> ft_2;

	UnitTester::assert_((ft_1 == ft_2) == true);
}

void _vector_operator_e_false()
{
	set_explanation_("wrong result on size difference");
	int             size_1 = 10;
	int             size_2 = 12;
	ft::vector<int> ft_1   = _set_vector(size_1, true);
	ft::vector<int> ft_2   = _set_vector(size_2, true);

	UnitTester::assert_((ft_1 == ft_2) == false);
}
void _vector_operator_e_false2()
{
	set_explanation_("wrong result on value and size difference");
	int             size_1 = 10;
	int             size_2 = 7;
	ft::vector<int> ft_1   = _set_vector(size_1);
	ft::vector<int> ft_2   = _set_vector(size_2);

	UnitTester::assert_((ft_1 == ft_2) == false);
}

void vector_operator_e()
{
	load_subtest_(_vector_operator_e_true);
	load_subtest_(_vector_operator_e_true_empty);
	load_subtest_(_vector_operator_e_false);
	load_subtest_(_vector_operator_e_false2);
}

// -------------------------------------------------------------------------- //
//                                 operator!=                                 //
// -------------------------------------------------------------------------- //

void _vector_operator_ne_true()
{
	set_explanation_("wrong result on value std::string");
	int                     size_1 = 2;
	int                     size_2 = 13;
	ft::vector<std::string> ft_1   = _set_vector_string(size_1);
	ft::vector<std::string> ft_2   = _set_vector_string(size_2);

	UnitTester::assert_((ft_1 != ft_2) == true);
}

void _vector_operator_ne_true2()
{
	set_explanation_("wrong result on different content");
	int                     size_1 = 24;
	int                     size_2 = size_1;
	ft::vector<std::string> ft_1   = _set_vector_string(size_1, true);
	ft::vector<std::string> ft_2   = _set_vector_string(size_2, true);

	UnitTester::assert_((ft_1 != ft_2) == true);
}

void _vector_operator_ne_false()
{
	set_explanation_("vector not same to itself!?");
	int                     size_1 = 10;
	ft::vector<std::string> ft_1   = _set_vector_string(size_1);

	UnitTester::assert_((ft_1 != ft_1) == false);
}

void vector_operator_ne()
{
	load_subtest_(_vector_operator_ne_true);
	load_subtest_(_vector_operator_ne_true2);
	load_subtest_(_vector_operator_ne_false);
}

// -------------------------------------------------------------------------- //
//                                 operator<                                 //
// -------------------------------------------------------------------------- //

void _vector_operator_l_true()
{
	set_explanation_("char vector size difference not evaluated correctly");
	int              size = 10;
	ft::vector<char> ft_0 = _set_vector_char(size, true);
	ft::vector<char> ft_1 = _set_vector_char(size, true);

	ft_0.pop_back();
	// _debug(ft_0, "0");
	// _debug(ft_1, "1");
	UnitTester::assert_((ft_0 < ft_1) == true);
}

void _vector_operator_l_false()
{
	set_explanation_("equal int values not evaluated correctly");
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size, true);

	UnitTester::assert_((ft < ft) == false);
}

void vector_operator_l()
{
	load_subtest_(_vector_operator_l_true);
	load_subtest_(_vector_operator_l_false);
}

// -------------------------------------------------------------------------- //
//                                 operator<=                                 //
// -------------------------------------------------------------------------- //

void _vector_operator_le_true()
{
	set_explanation_(
	    "std::string vector size difference not evaluated correctly");
	int                     size = 10;
	ft::vector<std::string> ft_0 = _set_vector_string(size, false);
	ft::vector<std::string> ft_1 = _set_vector_string(size, false);

	ft_0.pop_back();
	// _debug(ft_0, "0");
	// _debug(ft_1, "1");
	UnitTester::assert_((ft_0 <= ft_1) == true);
}

void _vector_operator_le_true2()
{
	set_explanation_("equal std::string values not evaluated correctly");
	int                     size = 10;
	ft::vector<std::string> ft   = _set_vector_string(size, true);

	UnitTester::assert_((ft <= ft) == true);
}

void _vector_operator_le_false()
{
	set_explanation_("char vector size difference not evaluated correctly");
	int              size_1 = 0;
	int              size_2 = 12;
	ft::vector<char> ft_1   = _set_vector_char(size_1, true);
	ft::vector<char> ft_2   = _set_vector_char(size_2, true);

	UnitTester::assert_((ft_2 <= ft_1) == false);
}

void vector_operator_le()
{
	load_subtest_(_vector_operator_le_true);
	load_subtest_(_vector_operator_le_true2);
	load_subtest_(_vector_operator_le_false);
}

// -------------------------------------------------------------------------- //
//                                 operator>                                  //
// -------------------------------------------------------------------------- //

void _vector_operator_g_true()
{
	set_explanation_("char vector size difference not evaluated correctly");
	int              size_1 = 21;
	int              size_2 = 12;
	ft::vector<char> ft_1   = _set_vector_char(size_1, true);
	ft::vector<char> ft_2   = _set_vector_char(size_2, true);

	UnitTester::assert_((ft_1 > ft_2) == true);
}

void _vector_operator_g_false()
{
	set_explanation_("equal std::string values not evaluated correctly");
	int                     size = 10;
	ft::vector<std::string> ft   = _set_vector_string(size, true);

	UnitTester::assert_((ft > ft) == false);
}

void vector_operator_g()
{
	load_subtest_(_vector_operator_g_true);
	load_subtest_(_vector_operator_g_false);
}

// -------------------------------------------------------------------------- //
//                                 operator>=                                 //
// -------------------------------------------------------------------------- //

void _vector_operator_ge_true()
{
	set_explanation_("equal int values not evaluated correctly");
	int             size = 42;
	ft::vector<int> ft   = _set_vector(size);

	UnitTester::assert_((ft >= ft) == true);
}

void _vector_operator_ge_compare()
{
	set_explanation_("char vector size difference not evaluated correctly");
	ft::vector<int>  ft_1;
	std::vector<int> std_1;
	_set_compare_vectors(ft_1, std_1);
	ft::vector<int>  ft_2;
	std::vector<int> std_2;
	_set_compare_vectors(ft_2, std_2);

	UnitTester::assert_((ft_1 >= ft_2) == (std_1 >= std_2));
}

void vector_operator_ge()
{
	load_subtest_(_vector_operator_ge_true);
	load_subtest_(_vector_operator_ge_compare);
}

// -------------------------------------------------------------------------- //
//                                  std::swap                                 //
// -------------------------------------------------------------------------- //

void _vector_std_swap_basic()
{
	set_explanation_("swapped value not correct");
	size_t          size_a = 10;
	size_t          size_b = 20;
	ft::vector<int> ft_a   = _set_vector(size_a, false);
	ft::vector<int> ft_b   = _set_vector(size_b, true);

	std::swap(ft_a, ft_b);
	for (size_t i = 0; i < size_b; ++i) {
		ft_a[i] = i;
	}
}

void _vector_std_swap_compare()
{
	set_explanation_("result differs from std");
	ft::vector<int>  ft_a;
	std::vector<int> std_a;
	_set_compare_vectors(ft_a, std_a);

	ft::vector<int>  ft_b;
	std::vector<int> std_b;
	_set_compare_vectors(ft_b, std_b);

	std::swap(ft_a, ft_b);
	std::swap(std_a, std_b);
	_compare_vectors(ft_a, std_a);
	_compare_vectors(ft_b, std_b);
}

void vector_std_swap()
{
	load_subtest_(_vector_std_swap_basic);
	load_subtest_(_vector_std_swap_compare);
}

} // namespace VectorTest
