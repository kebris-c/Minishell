/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:58:28 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/29 19:36:52 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "tokenizer.h"
# include "minishell.h"

/*
 *	Function Prototypes
 */
int		special_char(char c);
int		is_space(char c);
void	shred_program(t_shell *sh);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_redirs(t_redir *redirs);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
