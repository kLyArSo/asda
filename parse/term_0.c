#include "functions_headerfile.h"

char	*j_oin(char	*s, char	c)
{
	int		i;
	char	*ret;

	i = 0;
	if (s == NULL)
	{
		ret = my_calloc(2);
		if (ret == NULL)
			return (NULL);
		ret[0] = c;
		return (ret);
	}
	ret = my_calloc(ft_strlen(s) + 2);
	if (ret == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	free(s);
	return (ret);
}

int	fetch_char(struct termios	*old)
{
	char			c;
	int				summ;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	summ = 0;
	read(0, &c, 1);
	if (c != 27)
		return (c);
	else if (c == 27 && (read(0, &c, 1) != 0 && c == '['))
	{
		summ = 27;
		summ = summ + c;
		read(0, &c, 1);
		summ = summ + c;
	}
	tcsetattr(0, TCSANOW, old);
	return (summ);
}

char	*ft_strdupe(char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	if (str == NULL)
		return (NULL);
	ret = my_calloc((ft_strlen(str) + 1));
	if (ret == NULL)
		return (NULL);
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

int	put_char(int c)
{
	return (write(1, &c, 1));
}
