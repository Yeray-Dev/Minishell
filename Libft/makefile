# ========================
# CABECERA
# ========================

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ar rcs

# ========================
# ARCHIVOS FUENTE
# ========================

SRC =			ft_isdigit.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isprint.c\
				ft_strlen.c\
				ft_memset.c\
				ft_bzero.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_strlcpy.c\
				ft_strlcat.c\
				ft_toupper.c\
				ft_tolower.c\
				ft_strchr.c\
				ft_strncmp.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_strcmp.c\
				ft_strnstr.c\
				ft_atoi.c\
				ft_calloc.c\
				ft_strdup.c\
				ft_substr.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_itoa.c\
				ft_strrchr.c\
				ft_strmapi.c\
				ft_striteri.c\
				ft_split.c\
				ft_burbble_sort.c\
				ft_atoi_base.c\
				ft_strcpy.c\
				printf/ft_printf.c\
				printf/ft_redirect.c\
				printf/ft_hexa.c\
				GNL/get_next_line.c\
				GNL/get_next_line_utils.c

# ========================
# OBJETOS
# ========================

OBJECTS = $(SRC:.c=.o)

# # # INCLUDE =	libft.h/
# # # 			ft_printf/ft_printf.h/
# # # 			GNL/get_next_line.h

# ========================
# COMPILACIÓN
# ========================

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para ft_printf/
ft_printf/%.o: ft_printf/%.c
	@mkdir -p ft_printf
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para GNL/
GNL/%.o: GNL/%.c
	@mkdir -p GNL
	$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)

$(NAME): $(OBJECTS) # # # $(INCLUDE)
	$(LIB) $(NAME) $(OBJECTS)

# ========================
# CLEANING
# ========================

clean:
	rm -rf $(OBJECTS) $(BONUSOBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
