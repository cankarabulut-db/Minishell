#include "../minishell.h"

void quote_check(char *str)
{
	int i;
	int q_count;
	char c;

	q_count = 0;
	i = 0;


	while(str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && q_count % 2 == 0)
		{	
			c = str[i];
			q_count += 1;
		}
		else if (str[i] == c)
			q_count++;
		i++;
	}
	if (q_count % 2 != 0)
		printf("Error\n");
}

void start_parse(char *str)
{
	quote_check(str);
}