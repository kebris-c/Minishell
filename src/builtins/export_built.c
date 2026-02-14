/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:53:44 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 19:54:54 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	assigned_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
		return (0);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*extract_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	execute_export(t_cmd *cmd, t_shell *sh)
{
	int	i;

	i = 1;
	while (cmd->av[i])
		process_export_arg(cmd, sh, &i);
	return (0);
}

int	export_built(t_cmd *cmd, t_shell *sh)
{
	if (cmd->av[1] == NULL)
	{
		match_key_value(sh);
		return (0);
	}
	if (!check_valid_key(cmd->av[1]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd->av[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (execute_export(cmd, sh));
}
