#ifndef VectorTest_HPP
#define VectorTest_HPP

#include <list>

typedef struct s_unit_tests t_unit_tests;

class VectorTest
{
  public:
	static void vector_begin();
	static void vector_at();

	static t_unit_tests func_test_table[];

  private:
	static void _vector_begin_basic();

	static void _vector_at_basic();
	static void _vector_at_compare();
};

#endif /* VectorTest_HPP */
