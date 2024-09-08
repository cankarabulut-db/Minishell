#include "../minishell.h"

void empty_maker(char *str,char a,int start,int len)
{
	int i = 0;

	i = start;
	if(str[start] == DOUBLEQ || str[start] == SINGLEQ)
	{
		start++;
		while(len + i > start && str[start] && \
		(str[start] != DOUBLEQ && str[start] != SINGLEQ))
			str[start++] = a;
	}
	else
	{
		while(len + i > start && str[start] && \
		(str[start] != ' ' && str[start] != '\t'))
			str[start++] = a;
	}
	
}

int redirect_counter(char *str,int i,int redirectType)
{
	int count;

	count = 0;
	while(str[i])
	{
		if(str[i] == redirectType && str[i+1] == redirectType)
		{
			count++;
			i+=2;
		}
		else if(str[i] == redirectType)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}