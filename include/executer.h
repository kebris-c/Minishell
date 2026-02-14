/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:58:18 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 19:53:36 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "tokenizer.h"
# include "minishell.h"

/*
 *	Function Prototypes
 */
int		exec_cmds(t_cmd *cmds, t_shell *sh);
int		apply_redirs(t_cmd *cmd);
void	exec_command(t_exec_cmds *s, t_shell *sh);

#endif
