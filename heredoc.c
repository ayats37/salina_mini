/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:58:04 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:54:45 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_heredoc_interrupted = 0;

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
	exit(130);
}

void	handle_heredoc_input(char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

void	process_heredocs_tree(t_tree *node)
{
	t_token	*redir;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (!node)
		return ;
	g_heredoc_interrupted = 0;
	if (node->left)
	{
		process_heredocs_tree(node->left);
		if (g_heredoc_interrupted)
			return ;
	}
	if (node->right)
	{
		process_heredocs_tree(node->right);
		if (g_heredoc_interrupted)
			return ;
	}
	redir = node->redir;
	while (redir && !g_heredoc_interrupted)
	{
		if (redir->type == HEREDOC)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe failed");
				redir = redir->next;
				continue ;
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork failed");
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				redir = redir->next;
				continue ;
			}
			if (pid == 0)
			{
				close(pipe_fd[0]);
				signal(SIGINT, heredoc_sigint_handler);
				signal(SIGQUIT, SIG_IGN);
				handle_heredoc_input(redir->value, pipe_fd[1]);
				close(pipe_fd[1]);
				exit(0);
			}
			close(pipe_fd[1]);
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				close(pipe_fd[0]);
				redir->fd = -1;
				g_heredoc_interrupted = 1;
				signal(SIGINT, handler);
				reset_terminal_mode();
				return ;
			}
			else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			{
				close(pipe_fd[0]);
				redir->fd = -1;
				g_heredoc_interrupted = 1;
				signal(SIGINT, handler);
				reset_terminal_mode();
				return ;
			}
			else
				redir->fd = pipe_fd[0];
			signal(SIGINT, handler);
			reset_terminal_mode();
		}
		redir = redir->next;
	}
}

