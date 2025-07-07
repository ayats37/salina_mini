/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:31:55 by taya              #+#    #+#             */
/*   Updated: 2025/07/07 13:20:17 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void setup_shell_terminal(void)
{
    pid_t shell_pgid;

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    shell_pgid = getpid();
    if (setpgid(shell_pgid, shell_pgid) < 0)
    {
        perror("Couldn't put the shell in its own process group");
        exit(1);
    }
    if (tcsetpgrp(STDIN_FILENO, shell_pgid) < 0)
    {
        perror("Couldn't set terminal control");
        exit(1);
    }
}
#include <termios.h>

void    reset_terminal_mode(void)
{
    struct termios    term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    write(STDERR_FILENO, "\r\033[K", 4);
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void vv()
{
    system("leaks minishell");
}

int main(int argc, char **argv, char **env)
{
    char *input;
    t_lexer *lexer;
    t_token *token;
    t_token *token_list;
    t_tree *node;
    t_env *envlist;
    int last_exit_status = 0;
	// atexit(vv);
    
    (void)argc;
    (void)argv;
    input = NULL;
    lexer = NULL;
    node = NULL;
    token_list = NULL;
    
    envlist = init_env(env);
    setup_shell_terminal();
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handler);
    rl_catch_signals = 0;
    
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            write(1, "exit\n", 5);
            break;
        }
        
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        
        add_history(input);
          token_list = NULL;
        lexer = initialize_lexer(input);
        while (lexer->position < lexer->lenght)
        {
            token = get_next_token(lexer);
            if (!token)
                continue;
            token->type = token_type(token);
            append_token(&token_list, token);
        }
        free_lexer(lexer);
        lexer = NULL; 
        if (!token_list)
        {
            free(input);
            continue;
        }
        
        if (check_parenthesis(token_list) != 0)
        {
            free(input);
            free_token_list(token_list);
            continue;
        }
        
        if (merge_tokens(&token_list))
            free_token_list(token);
        
        if (check_errors(token_list) == 1)
        {
						last_exit_status = 258;
            free(input);
            free_token_list(token_list);
            continue;
        }   
        node = parse_op(token_list);
        if (!node)
        {
            free(input);
            free_token_list(token_list); 
            continue;
        }   
        // process_heredocs_tree(node);
        last_exit_status = execute_tree(node, &envlist, last_exit_status);
        free(input);
        free_token_list(token_list);
        free_tree(node);      
    }
    free_env_list(envlist);
    rl_clear_history(); 
    
    return (0);
}