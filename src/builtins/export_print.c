/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:26:13 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:26:15 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	count_total_vars(t_shell *sh)
{
	int	size;

	size = 0;
	while (sh->env && sh->env[size])
		size++;
	if (sh->export_only)
		size += array_length(sh->export_only);
	return (size);
}

char	*extract_env_key(char *env_str)
{
	int		j;
	char	*key;

	j = 0;
	while (env_str[j] && env_str[j] != '=')
		j++;
	key = malloc(sizeof(char) * (j + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_str, j + 1);
	return (key);
}

static int	add_env_keys(t_shell *sh, char **keys)
{
	int		i;
	char	*key;

	i = 0;
	while (sh->env && sh->env[i])
	{
		key = extract_env_key(sh->env[i]);
		if (!key)
		{
			free_array(keys, i);
			return (-1);
		}
		keys[i] = key;
		i++;
	}
	return (i);
}

static int	add_export_only_keys(t_shell *sh, char **keys, int start)
{
	int	i;
	int	k;

	if (!sh->export_only)
		return (start);
	i = start;
	k = 0;
	while (sh->export_only[k])
	{
		keys[i] = ft_strdup(sh->export_only[k]);
		if (!keys[i])
		{
			free_array(keys, i);
			return (-1);
		}
		i++;
		k++;
	}
	return (i);
}

char	**get_key(t_shell *sh)
{
	char	**keys;
	int		size;
	int		i;

	if (!sh || !sh->env)
		return (NULL);
	size = count_total_vars(sh);
	keys = malloc(sizeof(char *) * (size + 1));
	if (!keys)
		return (NULL);
	i = add_env_keys(sh, keys);
	if (i == -1)
		return (NULL);
	i = add_export_only_keys(sh, keys, i);
	if (i == -1)
		return (NULL);
	keys[i] = NULL;
	return (keys);
}
