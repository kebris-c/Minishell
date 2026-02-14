/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:28:48 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:28:49 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

static void	init_expand(t_expand *exp)
{
	exp->result = ft_strdup("");
	exp->i = 0;
	exp->in_squote = 0;
	exp->in_dquote = 0;
}

static char	*process_dollar(char *str, t_expand *exp, t_shell *sh)
{
	char	*value;

	value = handle_dollar_sign(str, &exp->i, sh);
	exp->result = ft_strjoin_free(exp->result, value, 1, 1);
	return (exp->result);
}

static char	*process_regular_char(char *str, t_expand *exp)
{
	exp->result = ft_strappend_char(exp->result, str[exp->i]);
	exp->i++;
	return (exp->result);
}

char	*expand_variables(const char *raw, t_shell *sh)
{
	t_expand	exp;
	char		*str;

	str = ft_strdup(raw);
	if (!str)
		return ((char *)raw);
	init_expand(&exp);
	while (str[exp.i])
	{
		if (exp.i > 0 && str[exp.i - 1] == '<' && str[exp.i] == '<')
			return ((char *)raw);
		handle_quotes(str[exp.i], &exp);
		if (str[exp.i] == '$' && !exp.in_squote)
			process_dollar(str, &exp, sh);
		else
			process_regular_char(str, &exp);
	}
	free(str);
	return (exp.result);
}
