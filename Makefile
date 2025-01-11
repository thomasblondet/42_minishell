NAME = minishell
HEADER = -I./include
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline
SRC = src/main.c

OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	cc $(CFLAGS) $< -o $@ libft/libft.a $(READLINE)

obj/%.o: src/%.c
	mkdir -p obj
	cc $(HEADER) -c $< -o $@

clean:
	make clean -C libft/
	rm -rf obj

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all