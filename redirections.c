/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:44:35 by taya              #+#    #+#             */
/*   Updated: 2025/07/07 11:54:35 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_redir(t_token *redir)
{
	if (redir->fd > 0)
	{
		if (dup2(redir->fd, STDIN_FILENO) == -1)
		{
			write_error_no_exit(NULL, "dup2 failed");
			return;
		}
		close(redir->fd);
	}
}

int	handle_input_redir(t_token *redir)
{
	int	fd;

	fd = open(redir->value, O_RDONLY);
	if (fd == -1)
	{
		write_error_no_exit(redir->value, "No such file or directory");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		write_error_no_exit(NULL, "dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_output_redir(t_token *redir)
{
	int	fd;

	if (redir->type == REDIR_OUT)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write_error_no_exit(redir->value, "Permission denied");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		write_error_no_exit(NULL, "dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redirection(t_tree *node)
{
	t_token	*redir;
	int		result;

	if (!node || !node->redir)
		return (0);
	redir = node->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			handle_heredoc_redir(redir);
		else if (redir->type == REDIR_IN)
		{
			result = handle_input_redir(redir);
			if (result != 0)
				return (result);
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
		{
			result = handle_output_redir(redir);
			if (result != 0)
				return (result);
		}
		redir = redir->next;
	}
	return (0);
}