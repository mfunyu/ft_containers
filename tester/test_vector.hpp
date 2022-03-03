#include "UnitTester.hpp"
#include <list>

namespace test_vector {

void vector_begin();

std::list<t_unit_tests> func_test_table(
	(t_unit_tests){"vector_begin", vector_begin}
);

} // namespace test_vector
