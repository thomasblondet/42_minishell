#include "minishell.h"

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("$   ");
		free(line);
	}
	return (0);
}