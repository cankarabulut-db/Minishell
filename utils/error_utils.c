#include "../minishell.h"

void error_msg(char *str1,int i)
{
	if(i == PIPE)
		printf("kurdishell : syntax error near unexpected token `|`\n");
	else if(i == 1)
		printf("kurdishell : syntax error near unexpected token `newline'\n");
	free(str1);
	exit(EXIT_FAILURE);
}
