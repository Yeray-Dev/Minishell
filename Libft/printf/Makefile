# NAME = libftprintf.a
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# LIB = ar rcs
# SRCs=			ft_printf.c\
# 				ft_redirect.c\
# 				ft_hexa.c

# OBJECTS = $(SRC:.c=.o)

# INCLUDE = ft_printf.h

# EXEC_SRC = main.c
# EXEC_OBJ = $(EXEC_SRC:.c=.o)
# EXEC = programa

# %.o: %.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# all: $(NAME)

# $(NAME): $(OBJECTS) $(INCLUDE)
# 	$(LIB) $(NAME) $(OBJECTS)

# $(EXEC): $(EXEC_OBJ) $(NAME)
# 	$(CC) $(EXEC_OBJ) -L. -lftprintf -o $(EXEC)

# clean:
# 	rm -rf $(OBJECTS) $(BONUSOBJECTS)

# fclean: clean
# 	rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re bonus

NAME = libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude 

SRC = $(shell find . -name '*.c')
OBJS = $(SRC:.c=.o)

TOTAL := $(words $(SRC))
all: $(NAME)
$(NAME): $(OBJS)
	@echo -e "\n🔗 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS)
	@echo "✅ Build complete"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@COMPILED=$$(find . -name '*.o' | wc -l); \
	BAR_WIDTH=30; \
	FILLED=$$((COMPILED * BAR_WIDTH / $(TOTAL))); \
	BAR=$$(printf "%0.s#" $$(seq 1 $$FILLED)); \
	SPACE=$$(printf "%0.s " $$(seq 1 $$((BAR_WIDTH - FILLED)))); \
	printf "\r[%s%s]" "$$BAR" "$$SPACE"


clean: # Limpia los arhivos .o locales
	$(RM) $(OBJS)
	@printf "\n Cleaned!\n"

fclean: clean # Limpia todos los archivos .o de todas las subrutas
	$(RM) $(NAME)

re: fclean all # Recompila desde 0, primero hace Fclean y luego compila

.PHONY: all clean fclean re