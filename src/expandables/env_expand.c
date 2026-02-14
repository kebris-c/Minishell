/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:28:30 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:28:31 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

static int	key_matches_env(char *env_var, char *key, int key_len)
{
	if (ft_strncmp(env_var, key, key_len) == 0
		&& env_var[key_len] == '=')
		return (1);
	return (0);
}

char	*get_env_value(char *key, t_shell *sh)
{
	int	i;
	int	key_len;

	if (!key || !sh || !sh->env)
		return (ft_strdup(""));
	key_len = ft_strlen(key);
	i = 0;
	while (sh->env[i])
	{
		if (key_matches_env(sh->env[i], key, key_len))
			return (ft_strdup(sh->env[i] + key_len + 1));
		i++;
	}
	return (ft_strdup(""));
}
