/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_loop_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 20:12:04 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/29 20:30:31 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"
#include "utils.h"

static void	free_hdoc(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

static void	no_line_case(t_redir *redir)
{
	ft_putstr_fd("Warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(redir->fname, 2);
	ft_putstr_fd("')\n", 2);
}

static int	auxiliar(char *line, int pipe_fd[2], char **buf, size_t *buf_len)
{
	size_t	line_len;
	char	*tmp;

	ft_putstr_fd(line, pipe_fd[1]);
	write(pipe_fd[1], "\n", 1);
	line_len = ft_strlen(line);
	tmp = ft_realloc(*buf, *buf_len, *buf_len + 1 + line_len + 1);
	if (!tmp)
	{
		free_hdoc(line, *buf);
		*buf = NULL;
		perror("ft_realloc");
		return (-1);
	}
	*buf = tmp;
	ft_memmove(*buf + *buf_len, line, line_len);
	free(line);
	*buf_len += line_len + 1;
	(*buf)[*buf_len - 1] = '\n';
	(*buf)[*buf_len] = '\0';
	return (0);
}

int	while_true_loop(t_redir *redir, int pipe_fd[2], \
		int stdin_backup, size_t buf_len)
{
	char	*line;
	char	*buf;

	buf = NULL;
	while (true)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free_hdoc(line, buf), dup2(stdin_backup, STDIN_FILENO), -1);
		if (!line)
		{
			no_line_case(redir);
			break ;
		}
		if (ft_strcmp(line, redir->fname) == 0)
		{
			free(line);
			break ;
		}
		if (auxiliar(line, pipe_fd, &buf, &buf_len) == -1)
			return (-1);
	}
	if (buf && *buf)
		add_history(buf);
	return (free(buf), 0);
}
