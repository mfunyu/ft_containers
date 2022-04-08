#include "UnitTester.hpp"

int main(int ac, char** av)
{
	int status;
	(void)ac;
	(void)av;
	UnitTester test;
	test.load_tests();
	status = test.run_tests();
	return (status);
}
