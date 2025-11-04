NAME = btc
CC = c++

SRCS = main.cpp BitcoinExchange.cpp\

CFLAGS = -Wall -Wextra -Werror -std=c++98 #-g
RM = rm -rf

OBJ_DIR		= obj/

OBJS        =    $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

DEF_COLOR    = \033[38;5;28m
YELLOW       =    \033[0;93m
B_COLOR		 = \033[0;39ms

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\n$(DEF_COLOR) $(NAME) is ready $(B_COLOR)"

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(YELLOW)."

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) -r $(NAME)

re: fclean all

.PHONY:        all re clean fclean
