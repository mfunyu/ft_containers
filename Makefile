# ---------------------------------------------------------------------------- #
# set path to your ft_container

PATH_TO_YOUR_CONTAINER := ./includes/

# ---------------------------------------------------------------------------- #
NAME	:= run_test
CXX		:= clang++
INCLUDES:= -Itest_srcs/includes -I$(PATH_TO_YOUR_CONTAINER)
CXXFLAGS:= -std=c++98 -pedantic-errors $(INCLUDES) -MMD -MP

# ---------------------------------------------------------------------------- #
# make
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

# ---------------------------------------------------------------------------- #
# make std
ifdef STD
CXXFLAGS += -DSTD
NAME	:= std_test
endif

# ---------------------------------------------------------------------------- #
# make bench
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
		SetTest_Bench.cpp
endif

# ---------------------------------------------------------------------------- #
OBJS_DIR:= objs/
OBJS	:= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
SRCS_DIR:= test_srcs
VPATH	:= $(SRCS_DIR) \
	$(SRCS_DIR)/vector \
	$(SRCS_DIR)/map \
	$(SRCS_DIR)/stack \
	$(SRCS_DIR)/set \
DEPS	:= $(OBJS:.o=.d)

# ---------------------------------------------------------------------------- #
# basic rules

.PHONY	: all clean fclean re test

all	: $(NAME)  ## Compile test with ft

-include $(DEPS)

$(NAME)	: $(OBJS_DIR) $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo executable: $@

$(OBJS_DIR)%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo compile: $<

$(OBJS_DIR):
	@-mkdir $@

clean	:  ## Remove obj directory
	$(RM) -R $(OBJS_DIR)

fclean	: clean ## Remove executable
	$(RM) $(NAME)

re	: fclean all

# ---------------------------------------------------------------------------- #
# advanced rules

ft	: re  ## Recompile test with ft

std	: ## Recompile test with std
	make re STD=1
	
std+	: ## Compile test with std
	make STD=1

test	: ## Compile main.c wtih both ft and std
	@$(CXX) $(CXXFLAGS) -o 42main.o -c 42main.cpp -D STD=1
	@$(CXX) $(CXXFLAGS) -o std_$@ 42main.o
	@echo executable: std_$@
	@$(CXX) $(CXXFLAGS) -o 42main.o -c 42main.cpp
	@$(CXX) $(CXXFLAGS) -o ft_$@ 42main.o
	@echo executable: ft_$@	
	
bench	: ## Compile benchmark test
	make BENCH=1

help	: ## Display this help screen
	@grep -E '^[a-zA-Z_-]+.*:.*?## .*$$' Makefile \
	| awk 'BEGIN {FS = "\t:.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'