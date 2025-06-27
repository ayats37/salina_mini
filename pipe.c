/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:34:44 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:55:58 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork failed");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	return (0);
}

void	child_process_left(t_tree *node, int pipe_fd[2], t_env **envlist,
		int last_status)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exit(execute_tree(node->left, envlist, last_status));
}

void	child_process_right(t_tree *node, int pipe_fd[2], t_env **envlist,
		int last_status)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	exit(execute_tree(node->right, envlist, last_status));
}

int	handle_fork_error(pid_t pid1, int pipe_fd[2])
{
	perror("fork failed");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	return (1);
}

int	execute_pipe(t_tree *node, t_env **envlist, int last_status)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (create_pipe_and_fork(pipe_fd, &pid1))
		return (1);
	if (pid1 == 0)
		child_process_left(node, pipe_fd, envlist, last_status);
	pid2 = fork();
	if (pid2 == -1)
		return (handle_fork_error(pid1, pipe_fd));
	if (pid2 == 0)
		child_process_right(node, pipe_fd, envlist, last_status);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}
