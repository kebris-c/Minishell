/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shred_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:07:36 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 20:08:25 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

void	shred_program(t_shell *sh)
{
	if (!sh)
		return ;
	ft_free_matrix(sh->export_only);
	ft_free_matrix(sh->to_export);
	ft_free_matrix(sh->env);
	free(sh);
}
