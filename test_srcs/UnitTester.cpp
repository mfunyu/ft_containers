#include "UnitTester.hpp"
#include "VectorTest.hpp"
#include <iostream>
#include <unistd.h>

std::list<t_unit_subtests> UnitTester::_func_subtest_table;
const char*                UnitTester::_current_func_name;
t_stl_types                UnitTester::_current_func_type;

UnitTester::UnitTester() : _cnt_success(0), _cnt_total(0) {}

UnitTester::~UnitTester() {}

void UnitTester::_load_test(t_unit_tests* func_test_table)
{
	for (size_t i = 0; func_test_table[i].func_name[0]; ++i) {
		_current_func_name = func_test_table[i].func_name;
		_current_func_type = func_test_table[i].type;
		func_test_table[i].func_test_ptr();
	}
}

void UnitTester::load_subtest(void (*func)(void), char* func_name)
{
	t_unit_subtests func_subtest;

	func_subtest.func_name     = _current_func_name;
	func_subtest.subtest_name  = func_name;
	func_subtest.func_test_ptr = func;
	func_subtest.type          = _current_func_type;
	_func_subtest_table.push_back(func_subtest);
}

void UnitTester::assert_(bool evaluate)
{
	if (evaluate == false)
		exit(TEST_FAILED);
}

void set_explanation(int* fds)
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	Log::_current_explanation = "";
	std::string line;
	while (std::getline(std::cin, line, '\n')) {
		if (!line.empty())
			Log::_current_explanation = line;
	}
	close(fds[0]);
	std::cin.clear();
	std::clearerr(stdin);
}

void UnitTester::_sandbox(t_unit_subtests& current_test)
{
	int   fds[2];
	pid_t pid;
	int   wstatus;

	if (pipe(fds))
		throw std::runtime_error("pipe");
	pid = fork();
	if (pid < 0)
		throw std::runtime_error("fork");
	if (pid == 0) {
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		current_test.func_test_ptr();
		exit(EXIT_SUCCESS);
	} else {
		wait(&wstatus);
		if (WIFEXITED(wstatus)) {
			current_test.result
			    = static_cast<t_test_status>(WEXITSTATUS(wstatus));
		} else if (WIFSIGNALED(wstatus)) {
			current_test.result = TEST_UNEXPECTED;
			std::cerr << "signal: " << WTERMSIG(wstatus) << std::endl;
		}
		set_explanation(fds);
	}
}

std::string _stl_type_to_string(t_stl_types type)
{
	switch (type) {
	case VECTOR:
		return "vector";
	case MAP:
		return "map";
	default:
		break;
	}
	return "";
}

void UnitTester::_print_subheader(const std::string& header)
{
	int fill_width = 42 - header.length();
	int leftside   = fill_width / 2;

	std::cout << std::setfill('=');
	std::cout << std::setw(leftside) << " ";
	std::cout << header;
	std::cout << std::setw(fill_width - leftside) << std::left << " "
	          << std::endl;
	std::cout << std::setfill(' ');
}

void UnitTester::_display_result(t_unit_subtests& current_test)
{
	static const char* prev_func_name;
	static t_stl_types type;
	std::string        type_stirng = _stl_type_to_string(current_test.type);

	if (type != current_test.type) {
		_print_subheader(type_stirng);
		type = current_test.type;
	}
	if (!prev_func_name || strcmp(prev_func_name, current_test.func_name)) {
		if (prev_func_name)
			std::cout << std::endl;

		std::string func_name(current_test.func_name);
		std::cout << std::left << std::setw(15)
		          << func_name.substr((type_stirng + '_').length()) << ": ";
		prev_func_name = current_test.func_name;
	}

	switch (current_test.result) {
	case TEST_SUCCESS:
		std::cout << COLOR_SUCCESS "[OK] " COLOR_CLEAR;
		_cnt_success += 1;
		break;
	case TEST_FAILED:
		std::cout << COLOR_FAILED "[KO] " COLOR_CLEAR;
		break;
	case TEST_UNEXPECTED:
		std::cout << COLOR_FAILED "[???] " COLOR_CLEAR;
		break;
	}
	std::cout << std::flush;
}

void UnitTester::_display_total()
{
	std::cout << COLOR_BORD << "\n\n[RESULT] ";
	if (_cnt_success == _cnt_total)
		std::cout << COLOR_SUCCESS;
	else
		std::cout << COLOR_FAILED;
	std::cout << _cnt_success << "/" << _cnt_total << COLOR_CLEAR;

	int score_persentage = 100 * _cnt_success / _cnt_total;
	std::cout << " tests passed (" << COLOR_BORD << score_persentage << "%"
	          << COLOR_CLEAR << ")" << std::endl;
}

void UnitTester::run_tests(void)
{
	std::list<t_unit_subtests>::iterator current = _func_subtest_table.begin();
	std::list<t_unit_subtests>::iterator it_end  = _func_subtest_table.end();

	for (; current != it_end; ++current) {
		_sandbox(*current);
		_display_result(*current);
		_log.write_to_logfile(*current);
		_cnt_total += 1;
	}
	_display_total();
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
