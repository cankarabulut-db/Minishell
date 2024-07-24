#include "../minishell.h"

void quote_check(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '"')
		{
			i++;
			while(str[i] != '"')
			{
				if(str[i] == '"')
					
			}
		}
	}
}

void start_parse(char *str)
{
	quote_check(str);
}