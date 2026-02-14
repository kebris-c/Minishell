/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:43:57 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/29 20:36:00 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "redirs.h"

static int	cleanup_heredoc_interrupt(int pipe_fd[2], int stdin_backup)
{
	if (pipe_fd[0] >= 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close(pipe_fd[1]);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	g_signal = 0;
	setup_prompt_signals();
	return (-1);
}

static int	auxiliar(t_redir *redir, int pipe_fd[2], int stdin_backup)
{
	int	ret;

	g_signal = 0;
	setup_heredoc_signals();
	ret = while_true_loop(redir, pipe_fd, stdin_backup, 0);
	setup_prompt_signals();
	if (ret == -1)
		return (cleanup_heredoc_interrupt(pipe_fd, stdin_backup));
	close(stdin_backup);
	close(pipe_fd[1]);
	redir->heredoc_fd = pipe_fd[0];
	return (0);
}

int	process_heredocs(t_cmd *cmds)
{
	t_redir	*redir;
	int		pipe_fd[2];
	int		stdin_backup;

	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->fname)
			{
				if (pipe(pipe_fd) == -1)
					return (perror("pipe"), -1);
				stdin_backup = dup(STDIN_FILENO);
				if (stdin_backup == -1)
					return (perror("dup"), close(pipe_fd[0]), \
							close(pipe_fd[1]), -1);
				if (auxiliar(redir, pipe_fd, stdin_backup) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
