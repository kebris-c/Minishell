/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:53:01 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/29 20:29:56 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_built(t_cmd *cmd, t_shell *sh)
{
	int	i;

	(void)cmd;
	i = 0;
	while (sh->env[i])
	{
		write(1, sh->env[i], ft_strlen(sh->env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
