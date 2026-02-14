/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:58:18 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/11 17:20:40 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRS_H
# define REDIRS_H

# include "tokenizer.h"
# include "minishell.h"

/*
 *	Function Prototypes
 */
int	add_to_redirs(t_token **tokens, t_cmd *cmd);
int	redir_cases(t_redir *redir);
int	apply_redirs(t_cmd *cmd);
int	is_redir(t_tokentype type);
int	process_heredocs(t_cmd *cmds);
int	while_true_loop(t_redir *redir, int pipe_fd[2], \
		int stdin_backup, size_t buf_len);

#endif
