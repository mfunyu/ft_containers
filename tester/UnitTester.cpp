#include "UnitTester.hpp"
#include "test_vector.hpp"

UnitTester::UnitTester() {}

UnitTester::~UnitTester() {}

void UnitTester::_load_test(t_unit_tests *func_test_table)
{
	for (size_t i = 0; func_test_table[i].func_name; ++i)
	{
		func_test_table[i].func_test_ptr();
	}
}

void UnitTester::load_subtest(void (*func)(void), char *funcname)
{
	static int	index = 0;

	t_unit_tests func_subtest;

	func_subtest.func_name = funcname;
	func_subtest.func_test_ptr = func;
}

void UnitTester::load_tests(void)
{
	_load_test(test_vector::func_test_table);
}

void UnitTester::launcher(int ac, char** av)
{
	(void)ac;
	(void)av;
}