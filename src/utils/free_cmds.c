/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:57:39 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 20:07:58 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->av)
			ft_free_matrix(cmds->av);
		if (cmds->redirs)
			free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}
