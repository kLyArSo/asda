#include "functions_headerfile.h"

char	*ft_error(char	*str)
{
	write(1, str, ft_strlen(str));
	return (NULL);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i] != 0)
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = 0;
	return (result);
}
