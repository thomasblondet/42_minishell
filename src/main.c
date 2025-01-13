#include "minishell.h"

void	lst_print(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		ft_putstr_fd(current->var_name, 1);
		ft_putstr_fd("\t", 1);
		ft_putstr_fd(current->var_value, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_data	data;

	(void)argc;
	(void)argv;
	shell_init(&data, env);
	while (1)
	{
		line = readline("$   ");
		tokenizer(&data, line);
		ft_tokenprint(&data.tokens);
		reinit(&data, line);
	}
	return (0);
}
