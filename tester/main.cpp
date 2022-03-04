#include "UnitTester.hpp"

int main(int ac, char** av) {
	(void)ac;
	(void)av;
	UnitTester test;
	test.load_tests();
	test.run_tests();
}
