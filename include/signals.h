/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:58:18 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/19 16:51:33 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/*
 *	externalize global here
 */
extern volatile sig_atomic_t	g_signal;

/*
 *	Function Prototypes
 */
//	setup signals
void	setup_prompt_signals(void);
void	setup_exec_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
//	signal handlers
void	prompt_handler(int sig);
void	heredoc_handler(int sig);

#endif
