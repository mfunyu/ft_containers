NAME	:= run_test
CXX		:= clang++
INCLUDES:= -Iincludes/ -Itest_srcs/includes
CXXFLAGS:= -std=c++98 -pedantic-errors $(INCLUDES) -MMD -MP

ifdef STD
CXXFLAGS += -DTEST
NAME	:= std_test
endif

SRCS	:= main.cpp \
		Log.cpp \
		UnitTester.cpp \
		VectorTest.cpp \
		VectorTest_Basic.cpp \
		VectorTest_ElementAccess.cpp \
		VectorTest_Iterators.cpp \
		VectorTest_Capacity.cpp \
		VectorTest_NonMemberFunctions.cpp \
		VectorTest_Modifiers.cpp \
		MapTest.cpp \
		MapTest_Basic.cpp \
		MapTest_ElementAccess.cpp \
		MapTest_Iterators.cpp \
		MapTest_Capacity.cpp \
		MapTest_Lookup.cpp \
		MapTest_Observers.cpp \
		MapTest_NonMemberFunctions.cpp \
		MapTest_Modifiers.cpp \
		StackTest.cpp \
		StackTest_Basic.cpp \
		StackTest_Else.cpp \
		StackTest_NonMemberFunctions.cpp \
		SetTest.cpp \
		SetTest_Basic.cpp \
		SetTest_Iterators.cpp \
		SetTest_Capacity.cpp \
		SetTest_Lookup.cpp \
		SetTest_Observers.cpp \
		SetTest_NonMemberFunctions.cpp \
		SetTest_Modifiers.cpp \

ifdef BENCH
CXXFLAGS += -DBENCH
NAME	:= bench_test
SRCS	:= main.cpp \
		Log.cpp \
		UnitTester.cpp \
		UnitTesterBench.cpp \
		VectorTest.cpp \
		VectorTest_Bench.cpp \
		MapTest.cpp \
		MapTest_Bench.cpp \
		StackTest.cpp \
		StackTest_Bench.cpp \
		SetTest.cpp \
		SetTest_Basic.cpp \
		SetTest_Iterators.cpp \
		SetTest_Capacity.cpp \
		SetTest_Lookup.cpp \
		SetTest_Observers.cpp \
		SetTest_NonMemberFunctions.cpp \
		SetTest_Modifiers.cpp
endif


OBJS_DIR:= objs/
OBJS	:= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
SRCS_DIR:= test_srcs
VPATH	:= $(SRCS_DIR) \
	$(SRCS_DIR)/vector \
	$(SRCS_DIR)/map \
	$(SRCS_DIR)/stack \
	$(SRCS_DIR)/set \
DEPS	:= $(OBJS:.o=.d)

.PHONY	: all clean fclean re test

all	: $(NAME)

-include $(DEPS)

$(NAME)	: $(OBJS_DIR) $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo executable: $@

$(OBJS_DIR)%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo compile: $<

$(OBJS_DIR):
	@-mkdir $@

clean	:
	$(RM) -R $(OBJS_DIR)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

std	:
	make re STD=1
	
std1	:
	make STD=1


ft: re

test	:
	@$(CXX) $(CXXFLAGS) -o 42main.o -c 42main.cpp -D STD=1
	@$(CXX) $(CXXFLAGS) -o std_$@ 42main.o
	@echo executable: std_$@
	@$(CXX) $(CXXFLAGS) -o 42main.o -c 42main.cpp
	@$(CXX) $(CXXFLAGS) -o ft_$@ 42main.o
	@echo executable: ft_$@	
	
bench	:
	make BENCH=1