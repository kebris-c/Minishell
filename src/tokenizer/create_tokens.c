/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:37:50 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 20:03:27 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"

/*
 *	Create token with the real token type and its value. Then, Append it at
 *	the end of the list
 */
t_token	*create_token(t_token **lst, t_tokentype type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = NULL;
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new), NULL);
	}
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
