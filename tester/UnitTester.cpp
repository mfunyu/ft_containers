#include "UnitTester.hpp"
#include "VectorTest.hpp"
#include <iostream>

std::list<t_unit_tests> UnitTester::_func_subtest_table;

UnitTester::UnitTester() {}

UnitTester::~UnitTester() {}

void UnitTester::_load_test(t_unit_tests *func_test_table)
{
	for (size_t i = 0; func_test_table[i].func_name[0]; ++i)
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
	_func_subtest_table.push_back(func_subtest);
}

void UnitTester::run_tests(void)
{
	std::list<t_unit_tests>::iterator current = _func_subtest_table.begin();
	std::list<t_unit_tests>::iterator it_end = _func_subtest_table.end();
	for (; current != it_end; ++current)
	{
		std::cout << "name: " << current->func_name << std::endl;
		current->func_test_ptr();
	}
}

void UnitTester::load_tests(void)
{
	_load_test(VectorTest::func_test_table);
}

void UnitTester::launcher(int ac, char** av)
{
	(void)ac;
	(void)av;
}