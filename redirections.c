/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:44:35 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:56:24 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_redir(t_token *redir)
{
	if (redir->fd > 0)
	{
		if (dup2(redir->fd, STDIN_FILENO) == -1)
			write_error(NULL, "dup2 failed");
		close(redir->fd);
	}
}

void	handle_input_redir(t_token *redir)
{
	int	fd;

	fd = open(redir->value, O_RDONLY);
	if (fd == -1)
		write_error(redir->value, "No such file or directory");
	if (dup2(fd, STDIN_FILENO) == -1)
		write_error(NULL, "dup2 failed");
	close(fd);
}

void	handle_output_redir(t_token *redir)
{
	int	fd;

	if (redir->type == REDIR_OUT)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		write_error(redir->value, "Permission denied");
	if (dup2(fd, STDOUT_FILENO) == -1)
		write_error(NULL, "dup2 failed");
	close(fd);
}

int	handle_redirection(t_tree *node)
{
	t_token	*redir;

	if (!node || !node->redir)
		return (0);
	redir = node->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			handle_heredoc_redir(redir);
		else if (redir->type == REDIR_IN)
			handle_input_redir(redir);
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
			handle_output_redir(redir);
		redir = redir->next;
	}
	return (0);
}
