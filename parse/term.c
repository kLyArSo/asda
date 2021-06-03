#include "functions_headerfile.h"

char	*delete_char(char	*str)
{
	int		i;
	char	*ret;

	if (ft_strlen(str) <= 0)
		return (str);
	ret = malloc(ft_strlen(str));
	i = 0;
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i - 1] = 0;
	free(str);
	return (ret);
}

int	all_sp(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (1);
	return (0);
}
