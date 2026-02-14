/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:42:23 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 21:41:17 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (B_NOT_BUILTIN);
	if (!ft_strcmp(cmd, "echo"))
		return (B_ECHO);
	else if (!ft_strcmp(cmd, "cd"))
		return (B_CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (B_PWD);
	else if (!ft_strcmp(cmd, "export"))
		return (B_EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (B_UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (B_ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (B_EXIT);
	return (B_NOT_BUILTIN);
}
