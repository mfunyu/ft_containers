#ifndef UNITTESTER_HPP
#define UNITTESTER_HPP

#include "Log.hpp"
#include <list>
#include <string>

#define COLOR_SUCCESS "\033[32m"
#define COLOR_FAILED  "\033[31m"
#define COLOR_BORD    "\033[1m"
#define COLOR_CLEAR   "\033[0m"

#define load_subtest_(x)    UnitTester::load_subtest(x, (char*)#x)
#define set_explanation_(x) std::cout << x << std::endl;

typedef enum e_test_status
{
	TEST_SUCCESS,
	TEST_FAILED,
	TEST_ILL,
	TEST_ABORT,
	TEST_BUS,
	TEST_SEGV,
	TEST_UNEXPECTED
} t_test_status;

typedef enum e_stl_types
{
	NONE,
	VECTOR,
	MAP
} t_stl_types;

typedef struct s_unit_tests
{
	const char* func_name;
	void (*func_test_ptr)();
	t_test_status result;
	t_stl_types   type;
} t_unit_tests;

typedef struct s_unit_subtests
{
	const char* func_name;
	const char* subtest_name;
	void (*func_test_ptr)();
	t_test_status result;
	t_stl_types   type;
} t_unit_subtests;

class UnitTester
{
  private:
	static std::list<t_unit_subtests> _func_subtest_table;
	static const char*                _current_func_name;
	static t_stl_types                _current_func_type;
	static const int                  k_subtest_block_width = 20;
	Log                               _log;
	int                               _cnt_success;
	int                               _cnt_total;

  public:
	UnitTester();
	~UnitTester();
	void load_tests();
	void run_tests();
	void launcher(int argc, char** argv);

	static void load_subtest(void (*func)(void), char* func_name);
	static void assert_(bool evaluate);

  private:
	void _load_test(t_unit_tests* func_test_table);
	void _sandbox(t_unit_subtests& current_test);
	void _display_result(t_unit_subtests& current_test);
	void _display_total();
	void _print_subheader(const std::string& header);
	void _set_test_result(t_unit_subtests& current_test, int wstatus);

	UnitTester(UnitTester const& other);
	UnitTester& operator=(UnitTester const& other);
};

#endif /* UNITTESTER_HPP */
