/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:52:40 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/11 17:54:52 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	matrix_len(char **av)
{
	int	len;

	len = 0;
	while (av[len])
		len++;
	return (len);
}

static void	loop(t_cmd *cmd, int i, int len)
{
	int	j;

	while (cmd->av[i])
	{
		j = 0;
		while (cmd->av[i][j])
		{
			if (cmd->av[i][j++] == '"')
				continue ;
			write(1, &cmd->av[i][j - 1], 1);
		}
		if (++i < len)
			write(1, " ", 1);
	}
}

int	echo_built(t_cmd *cmd)
{
	int	i;
	int	len;
	int	new_line;

	i = 1;
	new_line = 1;
	if (cmd->av[1] && ft_strcmp(cmd->av[1], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	len = matrix_len(cmd->av);
	loop(cmd, i, len);
	if (new_line)
		printf("\n");
	return (0);
}
