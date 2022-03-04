#include "UnitTester.hpp"
#include "VectorTest.hpp"
#include <iostream>
#include <unistd.h>

std::list<t_unit_tests> UnitTester::_func_subtest_table;

UnitTester::UnitTester() {}

UnitTester::~UnitTester() {}

void UnitTester::_load_test(t_unit_tests* func_test_table)
{
	for (size_t i = 0; func_test_table[i].func_name[0]; ++i) {
		func_test_table[i].func_test_ptr();
	}
}

void UnitTester::load_subtest(void (*func)(void), char* funcname)
{
	t_unit_tests func_subtest;

	func_subtest.func_name     = funcname;
	func_subtest.func_test_ptr = func;
	_func_subtest_table.push_back(func_subtest);
}

void UnitTester::_sandbox(t_unit_tests& current_test)
{
	int   wstatus;
	pid_t pid = fork();

	if (pid < 0)
		throw std::runtime_error("fork");
	if (pid == 0) {
		current_test.func_test_ptr();
		exit(EXIT_SUCCESS);
	} else {
		wait(&wstatus);
		if (WIFEXITED(wstatus)) {
			std::cout << WEXITSTATUS(wstatus) << std::endl;
			current_test.result
			    = static_cast<t_test_status>(WEXITSTATUS(wstatus));
		}
	}
}

void UnitTester::_display_result(t_unit_tests& current_test)
{
	switch (current_test.result) {
	case TEST_SUCCESS:
		std::cout << "[OK]" << std::endl;
		break;
	case TEST_FAILED:
		std::cout << "[KO]" << std::endl;
		break;
	}
}

void UnitTester::run_tests(void)
{
	std::list<t_unit_tests>::iterator current = _func_subtest_table.begin();
	std::list<t_unit_tests>::iterator it_end  = _func_subtest_table.end();

	for (; current != it_end; ++current) {
		_sandbox(*current);
		_display_result(*current);
		_log.write_to_logfile(*current);
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
