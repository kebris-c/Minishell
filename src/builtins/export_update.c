/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:26:33 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:26:35 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	find_export_only(t_shell *sh, char *key)
{
	int	i;
	int	key_len;

	if (!sh->export_only)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (sh->export_only[i])
	{
		if (ft_strncmp(sh->export_only[i], key, key_len) == 0
			&& (sh->export_only[i][key_len] == '='
			|| sh->export_only[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**remove_export_only(t_shell *sh, int index)
{
	char	**new_export;
	int		i;
	int		j;
	int		len;

	len = array_length(sh->export_only);
	new_export = malloc(sizeof(char *) * len);
	if (!new_export)
		return (sh->export_only);
	i = 0;
	j = 0;
	while (sh->export_only[i])
	{
		if (i != index)
			new_export[j++] = sh->export_only[i];
		else
			free(sh->export_only[i]);
		i++;
	}
	new_export[j] = NULL;
	free(sh->export_only);
	return (new_export);
}

static int	update_export_only(t_shell *sh, char *str, char *key)
{
	int		i;
	char	*new_str;

	i = find_export_only(sh, key);
	if (i == -1)
		return (0);
	if (assigned_value(str))
	{
		sh->export_only = remove_export_only(sh, i);
		sh->env = add_to_env(sh, str);
		return (1);
	}
	new_str = export_string(str);
	if (!new_str)
		return (0);
	free(sh->export_only[i]);
	sh->export_only[i] = new_str;
	return (1);
}

int	update_existing_var(t_shell *sh, char *str)
{
	char	*key;
	int		updated;

	key = extract_key(str);
	if (!key)
		return (0);
	updated = env_update(sh, str, key);
	if (!updated)
		updated = update_export_only(sh, str, key);
	free(key);
	return (updated);
}

void	process_export_arg(t_cmd *cmd, t_shell *sh, int *i)
{
	if (!check_valid_key(cmd->av[*i]))
	{
		(*i)++;
		return ;
	}
	if (update_existing_var(sh, cmd->av[*i]))
	{
		(*i)++;
		return ;
	}
	if (assigned_value(cmd->av[*i]))
		sh->env = add_to_env(sh, cmd->av[*i]);
	else
		sh->export_only = add_to_export_only(sh, cmd->av[*i]);
	(*i)++;
}
