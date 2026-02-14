/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:54:15 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/19 21:39:53 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	find_var_index(char **arr, char *key)
{
	int	i;
	int	key_len;

	if (!arr || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], key, key_len) == 0)
		{
			if (arr[i][key_len] == '=' || arr[i][key_len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

static char	**remove_var_at_index(char **arr, int index)
{
	char	**new_arr;
	int		i;
	int		j;
	int		len;

	len = array_length(arr);
	new_arr = malloc((len) * sizeof(char *));
	if (!new_arr)
		return (arr);
	i = 0;
	j = 0;
	while (arr[i])
	{
		if (i != index)
		{
			new_arr[j] = arr[i];
			j++;
		}
		else
			free(arr[i]);
		i++;
	}
	new_arr[j] = NULL;
	free(arr);
	return (new_arr);
}

static int	unset_from_env(t_shell *sh, char *key)
{
	int	index;

	index = find_var_index(sh->env, key);
	if (index != -1)
	{
		sh->env = remove_var_at_index(sh->env, index);
		return (1);
	}
	return (0);
}

static int	unset_from_export_only(t_shell *sh, char *key)
{
	int	index;

	if (!sh->export_only)
		return (0);
	index = find_var_index(sh->export_only, key);
	if (index != -1)
	{
		sh->export_only = remove_var_at_index(sh->export_only, index);
		return (1);
	}
	return (0);
}

int	unset_built(t_cmd *cmd, t_shell *sh)
{
	int	i;
	int	removed;

	if (!cmd->av[1])
		return (0);
	i = 1;
	while (cmd->av[i])
	{
		if (!check_valid_key(cmd->av[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			i++;
			continue ;
		}
		removed = unset_from_env(sh, cmd->av[i]);
		if (!removed)
			removed = unset_from_export_only(sh, cmd->av[i]);
		i++;
	}
	return (0);
}
