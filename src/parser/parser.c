/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:31:02 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/15 18:32:49 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirs.h"
#include "utils.h"

static t_cmd	*cmd_new(void)
{
	t_cmd	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->av = NULL;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}

static int	cmd_size(t_token *tokens)
{
	int		size;
	t_token	*prev;

	size = 0;
	prev = NULL;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type == T_WORD \
			&& (!prev || !is_redir(prev->type)))
			size++;
		prev = tokens;
		tokens = tokens->next;
	}
	return (size);
}

/*
 *	build cmds, av or redir, whatever is needed
 */
t_cmd	*cmd_builder(t_token **tokens, t_cmd *new, int i)
{
	int		cmdsize;

	cmdsize = cmd_size(*tokens);
	new->av = malloc(sizeof(char *) * (cmdsize + 1));
	if (!new->av)
		return (NULL);
	while (*tokens && (*tokens)->type != T_PIPE)
	{
		if ((*tokens)->type == T_WORD)
		{
			new->av[i] = ft_strdup((*tokens)->value);
			if (!new->av[i++])
				return (NULL);
		}
		else if (is_redir((*tokens)->type))
		{
			if (!add_to_redirs(tokens, new))
				return (ft_putstr_fd("Syntax error\n", 2), NULL);
		}
		*tokens = (*tokens)->next;
	}
	new->av[i] = NULL;
	return (new);
}

t_cmd	*parse_tokens(t_token *tokens, t_cmd *cmds, t_cmd *tail)
{
	t_cmd	*new;

	while (tokens)
	{
		new = cmd_new();
		if (!new)
			return (free_cmds(cmds), NULL);
		if (cmd_builder(&tokens, new, 0) == NULL)
			return (free_cmds(cmds), NULL);
		if (!new->av)
			return (free(new), free_cmds(cmds), NULL);
		if (!cmds)
		{
			cmds = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = new;
		}
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
