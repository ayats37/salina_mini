/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:50:21 by taya              #+#    #+#             */
/*   Updated: 2025/07/07 12:41:50 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	write_error(char *command, char *message)
// {
// 	int	exit_status;

// 	write(STDERR_FILENO, "minishell: ", 11);
// 	if (command)
// 	{
// 		write(STDERR_FILENO, command, strlen(command));
// 		write(STDERR_FILENO, ": ", 2);
// 	}
// 	write(STDERR_FILENO, message, strlen(message));
// 	write(STDERR_FILENO, "\n", 1);
// 	if (strstr(message, "command not found"))
// 		exit_status = 127;
// 	else if (strstr(message, "is a directory")
// 		|| strstr(message, "Permission denied"))
// 		exit_status = 126;
// 	else
// 		exit_status = 1;
// 	exit(exit_status);
// }

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	return (0);
}

char	*str_join_free(char *s1, const char *s2)
{
	char	*res;
	int		len;

	len = strlen(s1) + strlen(s2);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	strcpy(res, s1);
	strcat(res, s2);
	free(s1);
	return (res);
}
