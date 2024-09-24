#include "../minishell.h"

void redirect_size(t_rdr *rdrc, char *str)
{
	rdrc->ic = redirect_counter(str, 0, INPUT);
	rdrc->oc = redirect_counter(str, 0, OUTPUT);
	rdrc->ac = redirect_counter(str, 0, APPEND);
	rdrc->hc = redirect_counter(str, 0, HEREDOC);
}