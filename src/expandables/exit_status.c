/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:28:38 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:28:40 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

static char	*find_question_mark(char *str, int *pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			*pos = i;
			return (str + i);
		}
		i++;
	}
	*pos = -1;
	return (NULL);
}

static char	*build_result(char *before, char *status, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, status);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, after);
	free(temp);
	return (result);
}

char	*expand_exit_status(char *str, int last_exit)
{
	char	*status_str;
	char	*before;
	char	*after;
	char	*result;
	int		pos;

	if (!str || !find_question_mark(str, &pos))
		return (ft_strdup(str));
	status_str = ft_itoa_custom(last_exit);
	if (!status_str)
		return (ft_strdup(str));
	before = ft_substr(str, 0, pos);
	after = ft_strdup(str + pos + 2);
	result = build_result(before, status_str, after);
	free(before);
	free(after);
	free(status_str);
	if (!result)
		return (ft_strdup(str));
	return (result);
}
