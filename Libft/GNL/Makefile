NAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ar rcs
SRC =			get_next_line.c\
				get_next_line_utils.c


OBJECTS = $(SRC:.c=.o)
# BONUSOBJECTS = $(BONUSSRC:.c=.o)
INCLUDE = get_next_line.h

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJECTS) $(INCLUDE)
	$(LIB) $(NAME) $(OBJECTS)



clean:
	rm -rf $(OBJECTS) $(BONUSOBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
