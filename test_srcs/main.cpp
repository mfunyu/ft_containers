#include "UnitTester.hpp"

#ifdef BENCH
void end(void)__attribute__((destructor));

void end(void)
{
    system("leaks -q bench");
}
#endif

int main(int ac, char** av)
{
	int        status;
	UnitTester test;
	test.load_tests(ac, av);
#ifdef BENCH
	status = test.run_bench_tests();
#else
	status = test.run_tests();
#endif
	return (status);
}
