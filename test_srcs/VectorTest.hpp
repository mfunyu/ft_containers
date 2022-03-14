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
void vector_get_allocator();

/* Element access */
void vector_at();
void vector_subscript_operator();
void vector_front();
void vector_back();
void vector_data();

/* Iterators */
void vector_begin();
void vector_end();
void vector_rbegin();
void vector_rend();

/* Capacity */
void vector_empty();
void vector_size();
void vector_maxsize();
void vector_reverse();
void vector_capacity();

/* Modifiers */
void vector_clear();
void vector_insert();
void vector_erase();
void vector_push_back();
void vector_pop_back();
void vector_resize();
void vector_swap();

/* Non-member functions */
void vector_operator_e();
void vector_operator_ne();
void vector_operator_l();
void vector_operator_le();
void vector_operator_g();
void vector_operator_ge();
void vector_std_swap();

extern t_unit_tests func_test_table[TABLE_SIZE];

} // namespace VectorTest

#endif /* VectorTest_HPP */
