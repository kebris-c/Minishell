/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:26:42 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:26:44 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**allocate_array(int size)
{
	char	**new_arr;

	new_arr = malloc(sizeof(char *) * (size + 2));
	if (!new_arr)
		return (NULL);
	return (new_arr);
}

static void	copy_array(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

char	**add_to_env(t_shell *sh, char *str)
{
	int		i;
	char	**new_env;
	char	*processed;

	i = array_length(sh->env);
	new_env = allocate_array(i);
	if (!new_env)
		return (sh->env);
	copy_array(new_env, sh->env);
	processed = export_string(str);
	if (!processed)
	{
		free(new_env);
		return (sh->env);
	}
	new_env[i] = processed;
	new_env[i + 1] = NULL;
	free(sh->env);
	return (new_env);
}

int	env_update(t_shell *sh, char *str, char *key)
{
	int		i;
	char	*new_str;

	i = 0;
	while (sh->env && sh->env[i])
	{
		if (key_matches(sh->env[i], key))
		{
			new_str = export_string(str);
			if (!new_str)
				return (0);
			free(sh->env[i]);
			sh->env[i] = new_str;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**add_to_export_only(t_shell *sh, char *str)
{
	int		i;
	char	**new_export;
	char	*processed;

	i = array_length(sh->export_only);
	new_export = allocate_array(i);
	if (!new_export)
		return (sh->export_only);
	copy_array(new_export, sh->export_only);
	processed = export_string(str);
	if (!processed)
	{
		free(new_export);
		return (sh->export_only);
	}
	new_export[i] = processed;
	new_export[i + 1] = NULL;
	free(sh->export_only);
	return (new_export);
}
