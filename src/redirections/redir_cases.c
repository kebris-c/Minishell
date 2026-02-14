/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:28:39 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 19:59:40 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirs.h"

static int	case_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->fname, O_RDONLY);
	if (fd == -1)
		return (perror(redir->fname), 0);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), close(fd), 0);
	close(fd);
	return (1);
}

static int	case_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(redir->fname), 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), 0);
	close(fd);
	return (1);
}

static int	case_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(redir->fname), 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), 0);
	close(fd);
	return (1);
}

static int	case_heredoc(t_redir *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), close(redir->heredoc_fd), 0);
	close(redir->heredoc_fd);
	return (1);
}

int	redir_cases(t_redir *redir)
{
	if (redir->type == T_REDIR_IN)
	{
		if (!case_in(redir))
			return (0);
	}
	else if (redir->type == T_REDIR_OUT)
	{
		if (!case_out(redir))
			return (0);
	}
	else if (redir->type == T_REDIR_APPEND)
	{
		if (!case_append(redir))
			return (0);
	}
	else if (redir->type == T_HEREDOC)
	{
		if (!case_heredoc(redir))
			return (0);
	}
	return (1);
}
