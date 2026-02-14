/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:25:09 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:25:11 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_array(char **arr, int count)
{
	int	j;

	if (!arr)
		return ;
	j = 0;
	while (j < count)
	{
		if (arr[j])
			free(arr[j]);
		j++;
	}
	free(arr);
}

int	array_length(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	key_matches(char *env_var, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(env_var, key, key_len) == 0)
	{
		if (env_var[key_len] == '=' || env_var[key_len] == '\0')
			return (1);
	}
	return (0);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}
