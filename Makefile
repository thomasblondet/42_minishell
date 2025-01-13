NAME = minishell
HEADER = -I./include
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline
SRC = src/main.c src/init.c \
	src/lexer/scan_token.c src/lexer/create_token.c src/lexer/token_utils.c \
	src/expander/expander.c

OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	cc $(CFLAGS) $(OBJ) -o $@ libft/libft.a $(READLINE)

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	cc $(HEADER) -c $< -o $@

clean:
	make clean -C libft/
	rm -rf obj

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all