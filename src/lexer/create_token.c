#include "minishell.h"

int	pipe_token(t_token **tokens, int *i)
{
	t_token	*tmp;

	tmp = ft_tokennew(PIPE, "|", i);
	if (tmp == NULL)
		return (ft_tokenfree(tokens), 1);
	ft_tokenadd_back(tokens, tmp);
	return (0);
}

int	input_tokens(t_token **tokens, char *line, int *i)
{
	t_token	*tmp;

	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tmp = ft_tokennew(HEREDOC, "<<", i);
		if (tmp == NULL)
			return (ft_tokenfree(tokens), 1);
		ft_tokenadd_back(tokens, tmp);
	}
	else
	{
		tmp = ft_tokennew(IN, "<", i);
		if (tmp == NULL)
			return (ft_tokenfree(tokens), 1);
		ft_tokenadd_back(tokens, tmp);
	}
	return (0);
}

int	output_tokens(t_token **tokens, char *line, int *i)
{
	t_token *tmp;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tmp = ft_tokennew(APPEND, ">>", i);
		if (tmp == NULL)
			return (ft_tokenfree(tokens), 1);
		ft_tokenadd_back(tokens, tmp);
	}
	else
	{
		tmp = ft_tokennew(OUT, ">", i);
		if (tmp == NULL)
			return (ft_tokenfree(tokens), 1);
		ft_tokenadd_back(tokens, tmp);
	}
	return (0);
}
