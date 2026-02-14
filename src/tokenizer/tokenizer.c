/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:22:47 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/20 15:56:51 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include "builtins.h"
#include "utils.h"

static int	heredoc_case(t_token **tokens, int *i, char *line)
{
	int		start;
	char	*word;

	(*i) += 2;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (!line[*i] || special_char(line[*i]))
	{
		ft_putstr_fd("Syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (create_token(tokens, T_HEREDOC, NULL) == NULL)
		return (1);
	start = *i;
	while (line[*i] && !special_char(line[*i]) && !is_space(line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
	if (create_token(tokens, T_WORD, word) == NULL)
		return (1);
	return (0);
}

/*
 *	We use 2 functions auxiliars to the main loop in order to parse the
 *	type of the token to create and append it to the token list
 */

static int	handle_quote(t_token **tokens, char *line, int *i)
{
	int		quote;
	int		start;
	char	*word;

	quote = 0;
	start = *i;
	while (line[*i] && (quote || (!special_char(line[*i]) \
		&& !is_space(line[*i]))))
	{
		if (is_quote(line[*i]) && (quote == line[*i] || !quote))
			quote = (quote == line[*i]) * 0 + (!quote) * line[*i];
		(*i)++;
	}
	if (quote)
		return (ft_putstr_fd("Syntax error: unclosed quote\n", 2), 1);
	word = ft_substr(line, start, *i - start);
	if (!word)
		return (1);
	if (create_token(tokens, T_WORD, word) == NULL)
		return (free(word), 1);
	return (free(word), 0);
}

static int	aux_conds2(char *line, t_token **tokens, int *i)
{
	if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
	{
		if (heredoc_case(tokens, i, line) == 1)
			return (free_tokens(*tokens), 1);
	}
	else if (line[*i] == '<')
	{
		if (create_token(tokens, T_REDIR_IN, NULL) == NULL)
			return (free_tokens(*tokens), 1);
		(*i)++;
	}
	else
	{
		if (handle_quote(tokens, line, i) == 1)
			return (free_tokens(*tokens), 1);
	}
	return (0);
}

static int	aux_conds1(char *line, t_token **tokens, int *i)
{
	if (line[*i] == '|')
	{
		if (create_token(tokens, T_PIPE, NULL) == NULL)
			return (free_tokens(*tokens), 1);
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
	{
		if (create_token(tokens, T_REDIR_APPEND, NULL) == NULL)
			return (free_tokens(*tokens), 1);
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		if (create_token(tokens, T_REDIR_OUT, NULL) == NULL)
			return (free_tokens(*tokens), 1);
		(*i)++;
	}
	else
		return (aux_conds2(line, tokens, i));
	return (0);
}

/*
 *	Tokenize line. 
 */
t_token	*tokenize_line(char *line)
{
	int		i;
	t_token	*tokens;

	if (!line)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		if (aux_conds1(line, &tokens, &i))
			return (NULL);
	}
	return (tokens);
}
