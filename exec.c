/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:14 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:52:06 by ouel-afi         ###   ########.fr       */
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
	int	result;

	stdout_backup = dup(STDOUT_FILENO);
	if (node && node->redir)
		handle_redirection(node);
	result = dispatch_builtin(node->cmd, envlist);
	if (node && node->redir)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
	return (result);
}

int	execute_cmd(char **cmds, t_env *envlist, t_tree *node)
{
	pid_t	pid;
	int		status;
	char	*full_path;
	char	**env_array;

	pid = fork();
	if (pid == -1)
		write_error(cmds[0], "fork failed");
	if (pid == 0)
	{
		if (node && node->redir)
			handle_redirection(node);
		full_path = find_cmd_path(cmds[0], &envlist);
		if (!full_path)
			write_error(cmds[0], "command not found");
		env_array = env_list_to_array(envlist);
		if (!env_array)
			return (free(full_path), write_error(cmds[0],
					"environment conversion failed"), 1);
		execve(full_path, cmds, env_array);
		return (free(full_path), free_env_array(env_array), write_error(cmds[0],
				"command not found"), 1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
