/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:29:18 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:29:19 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

int	is_valid_var_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static char	*handle_special_case(char *str, int *i)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (!is_valid_var_char(str[*i], 1))
		return (ft_strdup(""));
	return (NULL);
}

static int	count_var_len(char *str, int start)
{
	int	len;
	int	i;

	len = 0;
	i = start;
	while (str[i] && is_valid_var_char(str[i], len == 0))
	{
		len++;
		i++;
	}
	return (len);
}

char	*extract_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*name;
	char	*special;

	start = *i;
	special = handle_special_case(str, i);
	if (special)
		return (special);
	len = count_var_len(str, start);
	*i += len;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str + start, len + 1);
	return (name);
}
