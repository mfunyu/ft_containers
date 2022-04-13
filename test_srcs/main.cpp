#include "UnitTester.hpp"

int main(int ac, char** av)
{
	int        status;
	UnitTester test;
	test.load_tests(ac, av);
	status = test.run_tests();
	return (status);
}
