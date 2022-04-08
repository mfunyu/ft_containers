#include "Log.hpp"
#include "UnitTester.hpp"
#include "VectorTest.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

namespace VectorTest {

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
	int             size = 10;
	ft::vector<int> ft   = _set_vector(size);
	ft::vector<int> ft2  = _set_vector(size + 100);

	set_explanation_("0 returned");
	UnitTester::assert_(ft.max_size() != 0);
	set_explanation_("multiple vectors does not return the same max value");
	UnitTester::assert_(ft.max_size() == ft2.max_size());
	set_explanation_("returned value not max");
	UnitTester::assert_((ft.max_size() == ft.get_allocator().max_size())
	                    || (ft.max_size() == std::numeric_limits<ptrdiff_t>::max()));
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

} // namespace VectorTest
