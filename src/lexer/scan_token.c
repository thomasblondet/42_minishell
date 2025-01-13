#include "minishell.h"

char    *single_quote(char *line, int *j)
{
    char    *str;
    int     start;

    (*j)++;
    start = *j;
    while (line[*j] && line[*j] != '\'')
    {
        (*j)++;
    }
    if (line[*j] == '\'')
        str = ft_substr(line, start, *j - start);
    (*j)++;   
    return (str);
}

int     is_in_str(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

char    *double_quotes(t_data *data, char *line, int *j)
{
    char    *str;
    char    *tmp;
    int     start;

    (*j)++;
    start = *j;
    while (line[*j] && line[*j] != '\"')
        (*j)++;
    if (line[*j] == '\"')
    {
        str = ft_substr(line, start, *j - start);
        if (is_in_str(str, '$'))
        {
            tmp = expander(data, str);
            (*j)++;
            return (tmp);
        }
    }
    (*j)++;
    return (str);
}

int    word(t_data *data, t_token **tokens, char *line, int *i)
{
    t_token *word;
    char    *tmp;
    int     start;
	int		j;

    start = *i;
	j = *i;
    word = NULL;
    if (line[j] == '\'')
    {
        tmp = single_quote(line, &j);
        word = ft_tokennew(WORD, tmp, i);
        if (word == NULL)
            return (ft_tokenfree(tokens), 1);
        ft_tokenadd_back(tokens, word);
        *i = j - 1;
        return (0);
    }
    else if (line[j] == '\"')
    {
        tmp = double_quotes(data, line, &j);
        word = ft_tokennew(WORD, tmp, i);
        if (word == NULL)
            return (ft_tokenfree(tokens), 1);
        ft_tokenadd_back(tokens, word);
        *i = j - 1;
        return (0);
    }
    else
    {
        while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '|' && line[j] != '<'
            && line[j] != '>')
            j++;
        tmp = ft_substr(line, *i, j - *i);
        if (is_in_str(tmp, '$'))
            tmp = expander(data, tmp);
        word = ft_tokennew(WORD, tmp, i);
        if (word == NULL)
            return (ft_tokenfree(tokens), 1);
        ft_tokenadd_back(tokens, word);
        *i = j - 1;
        return (0);
    }
}

int special_char(t_token **tokens, char *line, int *i)
{
    if (line[*i] == '|')
    {
        if (pipe_token(tokens, i))
            return (1);
    }
    else if (line[*i] == '<')
    {
        if (input_tokens(tokens, line, i))
            return (1);
    }
    else if (line[*i] == '>')
    {
        if (output_tokens(tokens, line, i))
            return (1);
    }
    return (0);
}

int tokenizer(t_data *data, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
            i++;
        if (line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            if (special_char(&data->tokens, line, &i))
                return (1);
        }
        else
        {
            if (word(data, &data->tokens, line, &i))
                return (1);
        }
        i++;
    }
    return (0);
}
