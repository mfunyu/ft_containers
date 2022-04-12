#include "MapTest.hpp"
#include "UnitTester.hpp"
#include <iostream>
#include <map>
#include <vector>

namespace MapTest {

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */

void _map_constructor_default()
{
	set_explanation_("result differs from std behavior");
	ft::map<int, int>  ft;
	std::map<int, int> std;
	_compare_maps(ft, std);
}

void _map_constructor_range()
{
	set_explanation_("result differs from std behavior");
	size_t             size     = 14;
	std::map<int, int> map_base = _set_map(size);

	ft::map<int, int>  ft(map_base.begin(), map_base.end());
	std::map<int, int> std(map_base.begin(), map_base.end());
	_compare_maps(ft, std);
}

void _map_constructor_copy()
{
	set_explanation_("copy result differs from std behavior");
	ft::map<int, std::string>  ft;
	std::map<int, std::string> std;
	_set_compare_maps(ft, std);

	ft::map<int, std::string>  ft_cpy(ft);
	std::map<int, std::string> std_cpy(std);
	_compare_maps(ft_cpy, std_cpy);
}

void map_constructor()
{
	load_subtest_(_map_constructor_default);
	load_subtest_(_map_constructor_range);
	load_subtest_(_map_constructor_copy);
}

} // namespace MapTest
