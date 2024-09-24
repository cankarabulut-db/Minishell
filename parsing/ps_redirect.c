#include "../minishell.h"

void	redirect_malloc(t_shell *cmd, char *str, t_rdr *rdrc)
{
	redirect_size(rdrc, str);
	if(rdrc->ic > 0)
	{
		cmd->input = malloc(sizeof(char *) * rdrc->ic + 1);
		if(!cmd->input)
			error_msg(str,14);
	}
	if(rdrc->oc > 0)
	{
		cmd->output = malloc(sizeof(char *) * rdrc->oc + 1);
		if(!cmd->output)
			error_msg(str,14);
	}
	if(rdrc->hc > 0)
	{
		cmd->heredoc = malloc(sizeof(char *) * rdrc->hc + 1);
		if(!cmd->heredoc)
			error_msg(str,14);
	}
	if(rdrc->ac > 0)
	{
		cmd->append = malloc(sizeof(char *) * rdrc->ac + 1);
		if(!cmd->append)
			error_msg(str,14);
	}
}

void redirect_fill_null(t_shell *cmd,t_rdr *rc)
{
	if(cmd->append)
		cmd->append[rc->ac] = NULL;
	if(cmd->heredoc)
		cmd->heredoc[rc->hc] = NULL;
	if(cmd->input)
		cmd->input[rc->ic] = NULL;
	if(cmd->output)
		cmd->output[rc->oc] = NULL;
}

int end_of_rdr(char *str, int i)
{
	int c;

	c = 0;
	if (is_quote(str[i]) && i++ && ++c)
	{
		//while(str[i])
		//{
		//	while(!is_quote(str[i]) && str[i])
		//	{
		//		i++;
		//		if(is_quote(str[i]) && ++i && ++c)
		//			break;
		//	}
		//	if (c % 2 == 0 && !is_quote(str[i]))
		//		break;
		//	if(is_quote(str[i]) && str[i] && ++i && ++c)
		//		continue;
	
		//	i++;
		//}
		while(str[i] != ' ' && str[i])
		{
			while(is_quote(str[i]) && str[i])
				i++;
			if(is_quote(str[i]) && ++i)
				continue;
			i++;
		}
	}
	else
		while (str[i] != ' ' && str[i] && !ft_rdrconfirmator(str[i]))
		{
			if(is_quote(str[i]) == 1 && i++)
			{
				while(!is_quote(str[i]) && str[i])
						i++;
					if(is_quote(str[i]) && i++)
						continue;
			}
			i++;
		}
		return (i);
}
void	redirects_filler(t_shell *cmd, char *str, t_rdr *count, int i)
{
	int	start;

	start = i;
	i = end_of_rdr(str,start);
	if (count->ic > count->icwhile && count->type == INPUT)
		cmd->input[count->icwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	else if (count->oc > count->ocwhile && count->type == OUTPUT)
		cmd->output[count->ocwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	else if (count->ac > count->acwhile && count->type == APPEND)
		cmd->append[count->acwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	else if (count->hc > count->hcwhile && count->type == HEREDOC)
		cmd->heredoc[count->hcwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	empty_maker(str, ' ', start, i - start);
}

void	redirect_find_fill(t_shell *cmd, char *str, int i, t_rdr *rdrcount)
{
	rdr_makezero(rdrcount);
	redirect_malloc(cmd, str, rdrcount);
	redirect_fill_null(cmd,rdrcount);
	while (str[i])
	{
		if (str[i] == INPUT || str[i] == OUTPUT || \
			str[i] == APPEND || str[i] == HEREDOC)
		{
			rdrcount->type = str[i];
			if (rdrcount->type == APPEND || rdrcount->type == HEREDOC)
			{
				str[i] = ' ';
				str[i + 1] = ' ';
				i += 2;
			}
			else if(rdrcount->type == INPUT || rdrcount->type == OUTPUT)
				str[i++] = ' ';
			while (str[i] == ' ')
				i++;
			redirects_filler(cmd, str, rdrcount, i);
		}
		i++;
	}
}