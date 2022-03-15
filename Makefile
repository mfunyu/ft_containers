NAME	:= run_test
CXX		:= clang++
INCLUDES:= includes/
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -pedantic-errors -I$(INCLUDES) -MMD -MP

SRCS_DIR:= test_srcs/
SRCS	:= $(shell find $(SRCS_DIR) -name "*.cpp" | xargs basename)
OBJS_DIR:= objs/
OBJS	:= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
VPATH	:= $(SRCS_DIR)
DEPS	:= $(OBJS:.o=.d)

.PHONY	: all clean fclean re

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


test	:
