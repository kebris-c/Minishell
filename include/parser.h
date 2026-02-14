/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:58:18 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/14 19:53:10 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

/*
 *	Function Prototypes
 */

t_cmd	*parse_tokens(t_token *tokens, t_cmd *cmds, t_cmd *tail);

#endif
