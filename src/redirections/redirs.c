/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:18:25 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 20:00:12 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirs.h"

static t_redir	*init_redir(t_token **tokens)
{
	t_redir	*new;

	if (!tokens || !(*tokens))
		return (NULL);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = (*tokens)->type;
	new->next = NULL;
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != T_WORD || !(*tokens)->value)
		return (free(new), NULL);
	new->fname = ft_strdup((*tokens)->value);
	if (!new->fname)
		return (free(new), NULL);
	new->heredoc_fd = -1;
	return (new);
}

int	add_to_redirs(t_token **tokens, t_cmd *cmd)
{
	t_redir	*new;
	t_redir	*tmp;

	if (!tokens || !*tokens || !(*tokens)->next \
		|| (*tokens)->next->type != T_WORD)
		return (0);
	new = init_redir(tokens);
	if (!new)
		return (0);
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
