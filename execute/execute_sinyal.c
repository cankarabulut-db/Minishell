#include "../minishell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);  
        rl_on_new_line();                   
        rl_replace_line("", 0);             
        rl_redisplay();                 
    }
}

void handle_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        exit(HEREDOC_P);                
    }
}

void set_signal(int mode)
{
    if (mode == MAIN_P)
    {
        signal(SIGINT, handle_sigint);     
        signal(SIGQUIT, SIG_IGN);        
    }
    else if (mode == CHILD_P)
    {
        signal(SIGINT, SIG_DFL);           
        signal(SIGQUIT, SIG_DFL);       
    }
    else if (mode == HEREDOC_P)
    {
        signal(SIGINT, handle_heredoc);     
        signal(SIGQUIT, SIG_IGN); 
    }
}
