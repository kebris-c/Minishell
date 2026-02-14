/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:23:18 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/11 17:52:07 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_builtin(t_cmd *cmd, t_shell *sh, t_builtintype builtin)
{
	int	status;

	status = 0;
	if (builtin == B_NOT_BUILTIN)
		return (status);
	else if (builtin == B_ECHO)
		status = echo_built(cmd);
	else if (builtin == B_CD)
		status = cd_built(cmd, sh);
	else if (builtin == B_PWD)
		status = pwd_built(cmd, sh);
	else if (builtin == B_EXPORT)
		status = export_built(cmd, sh);
	else if (builtin == B_UNSET)
		status = unset_built(cmd, sh);
	else if (builtin == B_ENV)
		status = env_built(cmd, sh);
	else if (builtin == B_EXIT)
		status = exit_built(cmd, sh);
	return (status);
}
