#include "functions_headerfile.h"

void	purge(char	**env, t_format	*ptr)
{
	if (ptr->pipes == NULL)
		cleanse_no_pipes(env, ptr);
	else if (ptr->pipes != NULL)
		cleanse_yes_pipes(env, ptr);
}
