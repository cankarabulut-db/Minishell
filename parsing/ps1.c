#include "../minishell.h"

void pipe_redirect_ba(char *str,int i)
{
	while(str[i])
	{
		if(str[i] == PIPE)
		{
			i++;
			if(str[i] == 0)
				error_msg(str,PIPE);
			while((str[i] >= '\t' && str[i] <= 13) || str[i] == ' ')
				i++;
			if(str[i] == 0)
				error_msg(str,PIPE);
		}
		i++;
	}
}

void heredoc_append_control(char *str,int i)
{
	while(str[i])
	{
		if((str[i] == HEREDOC && str[i + 1] == HEREDOC) || \
		(str[i] == APPEND && str[i+1] == APPEND))
		{
			i+=2;
			if(str[i] == 0)
				error_msg(str,1);
			while((str[i] >= '\t' && str[i] <= 13) || str[i] == ' ')
				i++;
			if(str[i] == 0)
				error_msg(str,1);
		}
		i++;
	}
}

void input_output_control(char *str,int i)
{
	while(str[i])
	{
		if(str[i] == INPUT || str[i] == OUTPUT)
		{
			i++;
			if(str[i] == 0)
				error_msg(str,1);
			while((str[i] >= '\t' && str[i] <= 13) || str[i] == ' ')
				i++;
			if(str[i] == 0)
				error_msg(str,1);
		}
		i++;
	}
}
void redirects_filler(t_shell *cmd,char *str,int type,int i)
{
	int start;
	static int redirect_count;

	redirect_count = 0;
	start = i;
	while(str[i] && (str[i] != '\t' || str[i] != ' '))
		i++;
	if(type == INPUT)
		cmd->input[redirect_count] = ft_substr(str,start,i - start);
	else if(type == OUTPUT)
		cmd->output[redirect_count] = ft_substr(str,start,i - start);
	printf("%s", cmd->input[0]);
	redirect_count++;
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
void redirect_malloc(t_shell *cmd,char *str,int type)
{
	int rcount;

	rcount = redirect_counter(str,0,type);
	if(type == INPUT)
		cmd->input = malloc(sizeof(char *) * rcount + 1);
	else if(type == OUTPUT)
		cmd->output = malloc(sizeof(char *) * rcount + 1);
	else if(type == HEREDOC)
		cmd->heredoc = malloc(sizeof(char *) * rcount + 1);
	else if(type == APPEND)
		cmd->append = malloc(sizeof(char *) * rcount + 1);
}
void redirect_finder(t_shell *cmd,char *str,int i,int type)
{
	while(str[i])
	{
		if(str[i] == INPUT || str[i] == OUTPUT || \
			str[i] == APPEND || str[i] == HEREDOC)
		{
			type = str[i];
			if(type == APPEND || type == HEREDOC)
				i+=2;
			else
				i++;
			while(str[i] == '\t' || str[i] == ' ')
				i++;
			int a = redirect_counter(str,0,APPEND);
			printf("%d", a);
			exit(1);
			redirect_malloc(cmd,str,type);
			redirects_filler(cmd,str,type,i);
		}
		i++;
	}
}

void split_pipe(t_shell *cmd,char *str,int i, int size)
{
	char **pipe_cmd;
	t_shell *temp;

	pipe_cmd = ft_split(str,PIPE);
	size = ft_strplen(pipe_cmd);
	cmd = malloc(sizeof(t_shell));
	temp = cmd;
	while(size > i)
	{
		heredoc_append_control(pipe_cmd[i],0);
		input_output_control(pipe_cmd[i],0);
		redirect_finder(cmd,pipe_cmd[i],0,0);
		cmd->next = malloc(sizeof(t_shell));
		cmd = cmd->next;
		i++;
	}
	cmd = temp;
}
void struct_filler(t_shell *cmd, char *str, int i)
{
	(void)i;
		if(ft_exist(str,PIPE,0))
			split_pipe(cmd,str,0,0);
}


