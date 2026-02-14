/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:28:20 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:28:22 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

static int	is_special_char(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '\0')
		return (1);
	return (0);
}

static char	*handle_question_mark(int *i, t_shell *sh)
{
	(*i)++;
	return (ft_itoa_custom(sh->last_exit));
}

static char	*handle_regular_var(char *str, int *i, t_shell *sh)
{
	char	*var_name;
	char	*value;

	var_name = extract_var_name(str, i);
	if (!var_name)
		return (ft_strdup(""));
	value = get_env_value(var_name, sh);
	free(var_name);
	return (value);
}

char	*handle_dollar_sign(char *str, int *i, t_shell *sh)
{
	(*i)++;
	if (str[*i] == '?')
		return (handle_question_mark(i, sh));
	if (is_special_char(str[*i]))
		return (ft_strdup("$"));
	return (handle_regular_var(str, i, sh));
}
