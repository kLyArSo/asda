#include "functions_headerfile.h"

void	cleanse_yes_pipes(char	**env, t_format	*ptr)
{
	t_pipes	*tmp_pipes;

	tmp_pipes = ptr->pipes;
	dollar_exception_yes_pipes(env, ptr);
	while (tmp_pipes != NULL)
	{
		purge_process(tmp_pipes, env);
		tmp_pipes = tmp_pipes->next;
	}
}
