#ifndef MAPTEST_HPP
#define MAPTEST_HPP

#include "UnitTester.hpp"
#include <iostream>
#include <map>

#if TEST
namespace ft = std;
#else
#include "map.hpp"
#endif

#define TABLE_SIZE 0xF00
typedef struct s_unit_tests t_unit_tests;

namespace MapTest {

void map_constructor();
void map_destructor();
void map_assignment_operator();
void map_get_allocator();

/* Element access */
void map_at();
void map_subscript_operator();

/* Iterators */
void map_begin();
void map_end();
void map_rbegin();
void map_rend();

/* Capacity */
void map_empty();
void map_size();
void map_max_size();

/* Modifiers */
void map_clear();
void map_insert();
void map_erase();
void map_swap();

/* Lookup */
void map_count();
void map_find();
void map_equal_range();
void map_lower_bound();
void map_upper_bound();

/* Observers */
void map_key_comp();
void map_value_comp();

/* Non-member functions */
void map_operator_e();
void map_operator_ne();
void map_operator_l();
void map_operator_le();
void map_operator_g();
void map_operator_ge();
void map_std_swap();

extern t_unit_tests func_test_table[TABLE_SIZE];

ft::map<int, int> _set_map(int size = 6, bool accend = false);
void              _set_compare_maps(
                 ft::map<int, std::string>& ft_data, std::map<int, std::string>& std_data, int size = 6);

/* --------------------------- template functions --------------------------- */

template <class Key, class T>
void _compare_maps(ft::map<Key, T>& ft, std::map<Key, T>& std)
{
	UnitTester::assert_(ft.size() == std.size());
	typename ft::map<Key, T>::iterator  it  = ft.begin();
	typename std::map<Key, T>::iterator its = std.begin();

	for (; it != ft.end(); ++it, ++its) {
		UnitTester::assert_(*it == *its);
	}
}

template <class Key, class T>
void _debug(ft::map<Key, T>& ft, std::string name = "")
{
	std::cerr << std::endl;
	std::cerr << "[" << name << "] ";
	std::cerr << "size=" << ft.size() << " | ";

	typename ft::map<Key, T>::iterator it = ft.begin();
	for (; it != ft.end(); ++it) {
		std::cerr << it->first << ": " << it->second << " ";
	}
	std::cerr << std::endl;
}

} // namespace MapTest

#endif /* MAPTEST_HPP */
