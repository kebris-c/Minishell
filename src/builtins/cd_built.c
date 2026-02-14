/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:51:27 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/19 21:20:02 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_built(t_cmd *cmd, t_shell *sh)
{
	char	*path;

	(void)sh;
	if (!cmd->av[1])
		return (1);
	path = cmd->av[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		printf("%s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}
