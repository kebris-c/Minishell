/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:19:46 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/11 18:28:29 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "executer.h"
#include "builtins.h"
#include "signals.h"
#include "parser.h"
#include "redirs.h"
#include "utils.h"
#include "expandables.h"

extern volatile sig_atomic_t	g_signal;

/*
 *	Main loop, part 2: parsing tokens, adding redirs
 */
static void	loop_part2(char *line, t_shell *sh)
{
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*tail;

	tokens = tokenize_line(line);
	free(line);
	if (!tokens)
		return ;
	cmds = NULL;
	tail = NULL;
	cmds = parse_tokens(tokens, cmds, tail);
	free_tokens(tokens);
	if (!cmds)
		return ;
	if (process_heredocs(cmds) == -1)
	{
		sh->last_exit = 130;
		free_cmds(cmds);
		return ;
	}
	sh->last_exit = exec_cmds(cmds, sh);
	free_cmds(cmds);
}

/*
 *	Main loop, part 1: get line, check signals, add_history and tokenize line
 */
int	minishell_loop(t_shell *sh)
{
	char	*line;

	while (true)
	{
		g_signal = 0;
		line = readline("minishell$ ");
		if (!line)
			return (exit_built(NULL, sh));
		if (ft_strcmp(line, "exit") == 0)
			return (free(line), exit_built(NULL, sh));
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		line = expand_variables(line, sh);
		loop_part2(line, sh);
	}
	return (sh->last_exit);
}
