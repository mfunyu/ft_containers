#include "MapTest.hpp"

namespace MapTest {

#define FAIL TEST_FAILED

t_unit_tests func_test_table[] = {
	{        "map_constructor",         map_constructor, FAIL, MAP},
	{         "map_destructor",          map_destructor, FAIL, MAP},
	{"map_assignment_operator", map_assignment_operator, FAIL, MAP},
	{	  "map_get_allocator",       map_get_allocator, FAIL, MAP},
 // --------------------------- Element access --------------------------- //
	{                 "map_at",                  map_at, FAIL, MAP},
	{ "map_subscript_operator",  map_subscript_operator, FAIL, MAP},
 // ------------------------------ Iterators ----------------------------- //
	{              "map_begin",               map_begin, FAIL, MAP},
    {                "map_end",                 map_end, FAIL, MAP},
	{             "map_rbegin",              map_rbegin, FAIL, MAP},
    {               "map_rend",                map_rend, FAIL, MAP},
 // ------------------------------ Capacity ----------------------------- //
	{              "map_empty",               map_empty, FAIL, MAP},
    {               "map_size",                map_size, FAIL, MAP},
	{           "map_max_size",            map_max_size, FAIL, MAP},
 /*
  // ------------------------------ Modifiers ----------------------------- //
  {              "map_clear",               map_clear, FAIL, MAP},
  {             "map_insert",              map_insert, FAIL, MAP},
  {              "map_erase",               map_erase, FAIL, MAP},
  {               "map_swap",                map_swap, FAIL, MAP},
  // ------------------------------- Lookup ------------------------------- //
  {              "map_count",               map_count, FAIL, MAP},
  {               "map_find",                map_find, FAIL, MAP},
  {        "map_equal_range",         map_equal_range, FAIL, MAP},
  {        "map_lower_bound",         map_lower_bound, FAIL, MAP},
  {        "map_upper_bound",         map_upper_bound, FAIL, MAP},
  // ------------------------------ Observers ----------------------------- //
  {           "map_key_comp",            map_key_comp, FAIL, MAP},
  {         "map_value_comp",          map_value_comp, FAIL, MAP},
  // ------------------------ Non-member functions ------------------------ //
  {         "map_operator_e",          map_operator_e, FAIL, MAP},
  {        "map_operator_ne",         map_operator_ne, FAIL, MAP},
  {         "map_operator_l",          map_operator_l, FAIL, MAP},
  {        "map_operator_le",         map_operator_le, FAIL, MAP},
  {         "map_operator_g",          map_operator_g, FAIL, MAP},
  {        "map_operator_ge",         map_operator_ge, FAIL, MAP},
  {           "map_std_swap",            map_std_swap, FAIL, MAP},
  */
  // ------------------- Terminater (Do not comment out) ------------------ //
	{                     "\0",                    NULL, FAIL, MAP}
};

ft::map<int, int> _set_map(int size, bool accend)
{
	ft::map<int, int> data;

	for (int i = 0; i < size; ++i) {
		if (accend) {
			data[i] = i;
		} else {
			data[i] = std::rand();
		}
	}
	return data;
}

void _set_compare_maps(
    ft::map<int, std::string>& ft_data, std::map<int, std::string>& std_data, int size)
{
	std::string val;
	std::string strs[]   = { "42", "Tokyo", "Hello", "World", "!" };
	size_t      patterns = 5;

	for (int i = 0; i < size; ++i) {
		int index = std::rand() % patterns;

		val = strs[index] + strs[std::max(index - 1, 0)];
		ft_data.insert(std::pair<int, std::string>(i, val));
		std_data.insert(std::pair<int, std::string>(i, val));
	}
}

} // namespace MapTest
