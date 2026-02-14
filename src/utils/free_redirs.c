/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:57:39 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 20:07:52 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->fname)
			free(redirs->fname);
		if (redirs->heredoc_fd >= 0)
			close(redirs->heredoc_fd);
		free(redirs);
		redirs = tmp;
	}
}
