#include "../minishell.h"

void error_msg(char *str)
{
	printf("%s",str);
	exit(EXIT_FAILURE);
}