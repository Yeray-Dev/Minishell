NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRC:.c=.o)

# Librerías necesarias
LIBS = -lreadline

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean -s
	@$(RM) $(OBJS)
	clear
	@printf "Cleaned!\n"

fclean: clean 
	@make -C $(LIBFT_DIR) fclean -s
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
