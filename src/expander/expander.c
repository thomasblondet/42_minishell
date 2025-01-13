#include "minishell.h"

char    *search_env(t_data *data, char *str)
{
    t_env   *current;
    char    *empty;
    char    *tmp;

    current = data->env;
    empty = ft_strdup("");
    while (current)
    {
        if (!strcmp(current->var_name, str))
        {
            tmp = ft_strdup(current->var_value);
            return (tmp);
        }
        current = current->next;
    }
    return (empty);
}

char *expander(t_data *data,  char *str)
{
    char *result = NULL;
    char *tmp = NULL;
    char *var = NULL;
    char *expand = NULL;
    int i = 0;
    int result_len = 0;

    result = ft_strdup("");
    while (str[i] != '\0')
    {
        if (str[i] == '$')
        {
            int j;
            j = i + 1;
            while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
                j++;
            var = ft_substr(str, i + 1, j - (i + 1));
            printf("Variable to expand: '%s'\n", var);
            expand = search_env(data, var);
            free(var);
            if (expand == NULL)
                expand = "";
            tmp = ft_substr(str, result_len, i - result_len);
            result = ft_strjoin(result, tmp);
            free(tmp);
            result = ft_strjoin(result, expand);
            free(expand);
            i = j;
            result_len = i;
        }
        else
        {
            tmp = ft_substr(str, i, 1);
            result = ft_strjoin(result, tmp);
            free(tmp);
            i++;
        }
    }
    return (result);
}
