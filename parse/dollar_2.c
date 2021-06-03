#include "functions_headerfile.h"

ssize_t	equal_sign(char		*str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	not_equ_m_one(t_env		*ptr, char	**env, int	i, int	equ)
{
	ptr->var_name = ft_substr(env[i], 0, equ - 1);
	ptr->var_content = ft_substr(env[i], equ + 1, ft_strlen(env[i]));
}

void	equ_m_one(t_env		*ptr, char	**env, int	i)
{
	 ptr->var_name = ft_strdup(env[i]);
	 ptr->var_content = ft_strdup("");
}

t_env	*fetch_all_variables(char	**env)
{
	int		i;
	int		equ;
	t_env	*ptr;
	t_env	*ret;

	i = 0;
	ptr = malloc(sizeof(t_env));
	ret = ptr;
	while (env[i] != NULL)
	{
		equ = equal_sign(env[i]);
		if (equ != -1)
			not_equ_m_one(ptr, env, i, equ);
		else if (equ == -1)
			equ_m_one(ptr, env, i);
		if (env[++i] != NULL)
		{
			ptr->next = malloc(sizeof(t_env));
			ptr = ptr->next;
			ptr->next = NULL;
		}
	}
	return (ret);
}

char	*ft_strdup(char	*str)
{
	char	*ret;
	int		i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) + 1;
	ret = my_calloc(i);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}
