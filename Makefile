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

OBJS_DIR:= objs/
OBJS	:= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
SRCS_DIR:= test_srcs
VPATH	:= $(SRCS_DIR) \
	$(SRCS_DIR)/vector \
	$(SRCS_DIR)/map \
	$(SRCS_DIR)/stack
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
