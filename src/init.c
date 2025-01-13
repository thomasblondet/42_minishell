#include "minishell.h"

void    reinit(t_data *data, char *line)
{
    ft_bzero(data->tokens, sizeof(t_token));
    ft_tokenfree(&data->tokens);
    free(line);
}

t_env   *find_last(t_env *env)
{
    if (!env)
        return (NULL);
    while (env->next)
        env = env->next;
    return (env);
}

void    add_back(t_env **env, t_env *new)
{
    t_env   *tail;

    if (!env)
        return ;
    if (!(*env))
    {
        *env = new;
        return ;
    }
    tail = find_last(*env);
    tail->next = new;
}
t_env   *new_node(char *env)
{
    t_env   *new;
    int     i;

    i = 0;
    new = ft_calloc(1, sizeof(t_env));
    if (!new)
        return (NULL);
    new->var = env;
    if (!new->var)
        return (NULL);
    while (env[i] != '=')
        i++;
    new->var_name = ft_substr(env, 0, i);
    if (!new->var_name)
        return (NULL);
    new->var_value = ft_substr(env, i + 1, ft_strlen(env) - i);
    if (!new->var_value)
        return (NULL);
    return (new);
}

void	shell_init(t_data *data, char **env)
{
    t_env   *new;

    while (*env)
    {
        new = new_node(*env);
        if (!new)
            return ;
        add_back(&data->env, new);
        env++;
    }
}
