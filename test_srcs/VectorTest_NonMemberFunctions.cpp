#include "Log.hpp"
#include "UnitTester.hpp"
#include "VectorTest.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

namespace VectorTest {

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
