#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "readline/readline.h"
# include <string.h>

typedef struct s_env
{
	char			*var;
	char			*var_name;
	char			*var_value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef enum e_type
{
	WORD,
	PIPE,
	IN,
	HEREDOC,
	OUT,
	APPEND
}					t_type;

typedef struct s_token
{
	t_type			type;
	const char		*lexeme;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	t_env			*env;
	t_token			*tokens;
}					t_data;

/* init */
void				shell_init(t_data *data, char **env);
void    			reinit(t_data *data, char *line);
/* lexer */
int					tokenizer(t_data *data, char *line);
int					pipe_token(t_token **tokens, int *i);
int					input_tokens(t_token **tokens, char *line, int *i);
int					output_tokens(t_token **tokens, char *line, int *i);
t_token				*ft_tokennew(t_type type, const char *lexeme, int *i);
t_token				*ft_tokenlast(t_token *tokens);
void				ft_tokenadd_back(t_token **tokens, t_token *new);
void				ft_tokenfree(t_token **tokens);
void				ft_tokenprint(t_token **tokens);
/* expander */
char    			*expander(t_data *data, char *str);

#endif