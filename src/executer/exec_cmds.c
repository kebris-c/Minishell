/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:28:15 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/12 16:00:32 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "builtins.h"
#include "signals.h"
#include "redirs.h"

static void	child(t_exec_cmds *s, t_shell *sh)
{
	t_builtintype	builtin;

	setup_child_signals();
	if (s->prev_fd != -1)
	{
		if (dup2(s->prev_fd, STDIN_FILENO) == -1)
			(perror("dup2"), exit(EXIT_FAILURE));
		close(s->prev_fd);
	}
	if (s->cmd->next)
	{
		if (dup2(s->pipe_fd[1], STDOUT_FILENO) == -1)
			(perror("dup2"), exit(EXIT_FAILURE));
		(close(s->pipe_fd[0]), close(s->pipe_fd[1]));
	}
	if (!apply_redirs(s->cmd))
		exit(EXIT_FAILURE);
	builtin = is_builtin(s->cmd->av[0]);
	if (builtin)
		exit(exec_builtin(s->cmd, sh, builtin));
	exec_command(s, sh);
}

static void	father(t_exec_cmds *s)
{
	if (s->prev_fd != -1)
		close(s->prev_fd);
	if (s->cmd->next)
	{
		s->prev_fd = s->pipe_fd[0];
		close(s->pipe_fd[1]);
	}
	else
		s->prev_fd = -1;
	s->last_pid = s->pid;
}

static int	divider(t_exec_cmds *s, t_shell *sh)
{
	while (s->cmd)
	{
		if (s->cmd->next && pipe(s->pipe_fd) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		s->pid = fork();
		if (s->pid == -1)
			return (perror("fork"), EXIT_FAILURE);
		if (s->pid == 0)
			child(s, sh);
		father(s);
		s->cmd = s->cmd->next;
	}
	return (EXIT_SUCCESS);
}

static int	signal_manage(t_exec_cmds s)
{
	if (WIFEXITED(s.status))
		return (WEXITSTATUS(s.status));
	else if (WIFSIGNALED(s.status))
	{
		if (WTERMSIG(s.status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(s.status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(s.status));
	}
	return (EXIT_SUCCESS);
}

int	exec_cmds(t_cmd *cmds, t_shell *sh)
{
	t_exec_cmds		s;

	s.cmd = cmds;
	s.prev_fd = -1;
	s.last_pid = -1;
	s.status = 0;
	if (is_builtin(s.cmd->av[0]) && !cmds->next)
	{
		s.fd[0] = dup(STDIN_FILENO);
		s.fd[1] = dup(STDOUT_FILENO);
		if (!apply_redirs(s.cmd))
			return (EXIT_FAILURE);
		setup_exec_signals();
		s.status = exec_builtin(s.cmd, sh, is_builtin(s.cmd->av[0]));
		(dup2(s.fd[0], STDIN_FILENO), dup2(s.fd[1], STDOUT_FILENO));
		(close(s.fd[0]), close(s.fd[1]));
		return (setup_prompt_signals(), s.status);
	}
	setup_exec_signals();
	if (divider(&s, sh) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	waitpid(s.last_pid, &s.status, 0);
	while (wait(NULL) > 0)
		;
	return (setup_prompt_signals(), signal_manage(s));
}
