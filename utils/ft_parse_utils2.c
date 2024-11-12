#include "../minishell.h"

void redirect_size(t_rdr *rdrc, char *str, t_shell *cmd)
{
	rdrc->ic = redirect_counter(str, 0, INPUT);
	if (rdrc->ic == 0)
		cmd->input = NULL;
	rdrc->oc = redirect_counter(str, 0, OUTPUT);
	if (rdrc->oc == 0)
		cmd->output = NULL;
	rdrc->ac = redirect_counter(str, 0, APPEND);
	if (rdrc->ac == 0)
		cmd->append = NULL;
	rdrc->hc = redirect_counter(str, 0, HEREDOC);
	if (rdrc->hc == 0)
		cmd->heredoc = NULL;
}