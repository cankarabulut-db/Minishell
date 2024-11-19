#include "../minishell.h"

void heredoc_init(t_shell *cmd,int i)
{
	char *str;

	while(cmd->heredoc[i])
	{
		str = readline(">");
		while(ft_strequ(str,cmd->heredoc[i+1]))
		{
			cmd->heredoc[i] = ft_strdup(str);
			str = readline(">");
		}

	}
}