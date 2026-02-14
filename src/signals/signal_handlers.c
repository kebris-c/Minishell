/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:44:45 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/19 21:56:12 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	prompt_handler(int sig)
{
	(void)sig;
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_handler(int sig)
{
	(void)sig;
	g_signal = sig;
	close(STDIN_FILENO);
}
