/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:28:55 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:28:56 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

int	handle_quotes(char c, t_expand *exp)
{
	if (c == '\'' && !exp->in_dquote)
	{
		exp->in_squote = !exp->in_squote;
		return (1);
	}
	if (c == '"' && !exp->in_squote)
	{
		exp->in_dquote = !exp->in_dquote;
		return (1);
	}
	return (0);
}

int	should_expand(t_expand *exp)
{
	if (exp->in_squote)
		return (0);
	return (1);
}
