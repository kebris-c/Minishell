/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:53:26 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/19 21:48:56 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	exit_built(t_cmd *cmd, t_shell *sh)
{
	long	status;

	ft_putstr_fd("exit\n", 2);
	if (!cmd || !cmd->av[1])
		exit(sh->last_exit);
	if (!is_numeric(cmd->av[1]))
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(cmd->av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (cmd->av[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	status = ft_atol(cmd->av[1]);
	exit((unsigned char)status);
}
