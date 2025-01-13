#include "minishell.h"

void    ft_tokenprint(t_token **tokens)
{
    t_token *current;

    current = *tokens;
    while (current != NULL)
    {
        printf("%s [%d]\n", current->lexeme, current->type);
        current = current->next;
    }
}

void    ft_tokenfree(t_token **tokens)
{
    t_token  *tmp;

    while (*tokens != NULL)
    {
        tmp = *tokens;
        *tokens = (*tokens)->next;
        free(tmp);
    }
}

t_token *ft_tokenlast(t_token *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

void	ft_tokenadd_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (tokens == NULL)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	last = ft_tokenlast(*tokens);
	last->next = new;
}

t_token	*ft_tokennew(t_type type, const char *lexeme, int *i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
    new->lexeme = lexeme;
	new->next = NULL;
    if (type == HEREDOC || type == APPEND)
		(*i)++;
	return (new);
}
