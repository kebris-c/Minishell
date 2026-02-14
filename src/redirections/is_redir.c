/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:42:34 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 19:58:20 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

int	is_redir(t_tokentype type)
{
	if (type == T_REDIR_IN || type == T_REDIR_OUT \
		|| type == T_REDIR_APPEND || type == T_HEREDOC)
		return (1);
	return (0);
}
