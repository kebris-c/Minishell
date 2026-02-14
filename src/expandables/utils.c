/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:29:04 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:29:06 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (result);
}

static char	*copy_and_append(char *str, char c, int len)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (str);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

char	*ft_strappend_char(char *str, char c)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	return (copy_and_append(str, c, len));
}
