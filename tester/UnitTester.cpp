#include "UnitTester.hpp"
#include "test_vector.hpp"

UnitTester::UnitTester() {}

UnitTester::~UnitTester() {}

void UnitTester::_load_test(std::list<t_unit_tests> fun_test_table)
{
	std::list<t_unit_tests>::iterator current = fun_test_table.begin();
	std::list<t_unit_tests>::iterator it_end = fun_test_table.end();
	for (; current != it_end; ++current)
	{
		current->func_test_ptr();
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