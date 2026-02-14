/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:26:00 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:26:03 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	bubble_sort(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[j + 1])
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	find_value_in_env(char *key, t_shell *sh)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (sh->env[i])
	{
		if (ft_strncmp(key, sh->env[i], key_len) == 0
			&& sh->env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	print_value(char *key, t_shell *sh)
{
	int		index;
	int		key_len;
	char	*value;

	index = find_value_in_env(key, sh);
	if (index == -1)
		return ;
	key_len = ft_strlen(key);
	value = sh->env[index] + key_len + 1;
	write(1, "=\"", 2);
	write(1, value, ft_strlen(value));
	write(1, "\"", 1);
}

static void	print_export_line(char *key, t_shell *sh)
{
	write(1, "declare -x ", 11);
	write(1, key, ft_strlen(key));
	print_value(key, sh);
	write(1, "\n", 1);
}

void	match_key_value(t_shell *sh)
{
	char	**keys;
	int		i;

	keys = get_key(sh);
	if (!keys)
		return ;
	bubble_sort(keys);
	i = 0;
	while (keys[i])
	{
		print_export_line(keys[i], sh);
		i++;
	}
	free_array(keys, i);
}
