#include "functions_headerfile.h"

t_linedata	*fetch_red(char	*input, t_bag	*bag, t_linedata	*data)
{
	data = pre_red(input, bag, data);
	data = red(input, bag, data);
	return (data);
}
