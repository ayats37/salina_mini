/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:14 by taya              #+#    #+#             */
/*   Updated: 2025/07/07 13:05:30 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch_builtin(char **cmd, t_env **envlist)
{
	if (strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	if (strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, *envlist));
	if (strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	if (strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, envlist));
	if (strcmp(cmd[0], "unset") == 0)
		return (ft_unset(cmd, envlist));
	if (strcmp(cmd[0], "env") == 0)
		return (ft_env(envlist));
	if (strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, *envlist));
	return (0);
}

int	execute_builtin(t_tree *node, t_env **envlist)
{
	int	stdout_backup;
	int	stdin_backup;
	int	result;
	int	redir_result;

	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	
	if (node && node->redir)
	{
		redir_result = handle_redirection(node);
		if (redir_result != 0)
		{
			dup2(stdout_backup, STDOUT_FILENO);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdout_backup);
			close(stdin_backup);
			return (redir_result);
		}
	}
	
	result = dispatch_builtin(node->cmd, envlist);
	
	if (node && node->redir)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		dup2(stdin_backup, STDIN_FILENO);
		close(stdout_backup);
		close(stdin_backup);
	}
	
	return (result);
}

void	write_error_no_exit(char *command, char *message)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (command)
	{
		write(STDERR_FILENO, command, strlen(command));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

int	execute_cmd(char **cmds, t_env *envlist, t_tree *node)
{
	pid_t	pid;
	int		status;
	char	*full_path;
	char	**env_array;
	int		redir_result;

	pid = fork();
	if (pid == -1)
	{
		write_error_no_exit(cmds[0], "fork failed");
		return (1);
	}
	if (pid == 0)
	{
		if (node && node->redir)
		{
			redir_result = handle_redirection(node);
			if (redir_result != 0)
				exit(redir_result);
		}
		
		full_path = find_cmd_path(cmds[0], &envlist);
		if (!full_path)
		{
			write_error_no_exit(cmds[0], "command not found");
			exit(127);
		}
		if (access(full_path, X_OK) != 0)
		{
			write_error_no_exit(cmds[0], "Permission denied");
			free(full_path);
			exit(126);
		}
		env_array = env_list_to_array(envlist);
		if (!env_array)
		{
			free(full_path);
			write_error_no_exit(cmds[0], "environment conversion failed");
			exit(1);
		}	
		execve(full_path, cmds, env_array);
		free(full_path);
		free_env_array(env_array);
		write_error_no_exit(cmds[0], "command not found");
		exit(127);
	}
	waitpid(pid, &status, 0);
	
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	
	return (1);
}
