#ifndef VectorTest_HPP
#define VectorTest_HPP

#include <list>
#define TABLE_SIZE 0xF00

typedef struct s_unit_tests t_unit_tests;

namespace VectorTest {

void vector_constructor();
void vector_destructor();
void vector_assignment_operator();
void vector_assign();
void vector_at();
void vector_subscript_operator();
void vector_begin();
void vector_size();
void vector_empty();

extern t_unit_tests func_test_table[TABLE_SIZE];

} // namespace VectorTest

#endif /* VectorTest_HPP */
