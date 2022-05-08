#include "MapTest.hpp"
#include "UnitTester.hpp"
#include <map>

namespace MapTest {

/* -------------------------------------------------------------------------- */
/*                            benchmark operator[]                            */
/* -------------------------------------------------------------------------- */
void _bench_map_subscript_operator_ft()
{
	size_t            size   = 10000;
	ft::map<int, int> ft_src = _set_map(size, false);
}

void _bench_map_subscript_operator_std()
{
	size_t             size   = 10000;
	std::map<int, int> ft_src = _set_map_std(size, false);
}

void bench_map_subscript_operator()
{
	load_subtest_(_bench_map_subscript_operator_std);
	load_subtest_(_bench_map_subscript_operator_ft);
}

/* -------------------------------------------------------------------------- */
/*                              benchmark insert                              */
/* -------------------------------------------------------------------------- */
void _bench_map_insert_ft()
{
	ft::map<int, int> ft;
	size_t            count = 10000;

	for (int i = 0; i < count; ++i) {
		ft.insert(ft::make_pair(i, i));
	}
}

void _bench_map_insert_std()
{
	std::map<int, int> std;
	size_t             count = 10000;

	for (int i = 0; i < count; ++i) {
		std.insert(std::make_pair(i, i));
	}
}

void bench_map_insert()
{
	load_subtest_(_bench_map_insert_std);
	load_subtest_(_bench_map_insert_ft);
}

/* -------------------------------------------------------------------------- */
/*                               benchmark erase                              */
/* -------------------------------------------------------------------------- */
void _bench_map_erase_ft()
{
	int               size = 10000;
	ft::map<int, int> ft   = _set_map(size, true);

	for (int i = 0; i < 1000; ++i) {
		ft.erase(ft.begin());
	}
}

void _bench_map_erase_std()
{
	int                size = 10000;
	std::map<int, int> std  = _set_map_std(size, true);

	for (int i = 0; i < 1000; ++i) {
		std.erase(std.begin());
	}
}

void bench_map_erase()
{
	load_subtest_(_bench_map_erase_std);
	load_subtest_(_bench_map_erase_ft);
}

/* -------------------------------------------------------------------------- */
/*                               benchmark find                               */
/* -------------------------------------------------------------------------- */
void _bench_map_find_ft()
{
	int               size = 10000;
	ft::map<int, int> ft   = _set_map(size, false);

	for (int i = 0; i < 10000; ++i) {
		ft.find(i);
	}
}
void _bench_map_find_std()
{
	int                size = 10000;
	std::map<int, int> std  = _set_map_std(size, false);

	for (int i = 0; i < 10000; ++i) {
		std.find(i);
	}
}

void bench_map_find()
{
	load_subtest_(_bench_map_find_std);
	load_subtest_(_bench_map_find_ft);
}

/* -------------------------------------------------------------------------- */
/*                            benchmark equal_range                           */
/* -------------------------------------------------------------------------- */
void _bench_map_equal_range_ft()
{
	int               size = 10000;
	ft::map<int, int> ft   = _set_map(size, false);

	for (int i = 0; i < 10000; ++i) {
		ft.equal_range(i);
	}
}

void _bench_map_equal_range_std()
{
	int                size = 10000;
	std::map<int, int> std  = _set_map_std(size, false);

	for (int i = 0; i < 10000; ++i) {
		std.equal_range(i);
	}
}

void bench_map_equal_range()
{
	load_subtest_(_bench_map_equal_range_std);
	load_subtest_(_bench_map_equal_range_ft);
}

} // namespace MapTest
