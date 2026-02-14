/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:49:20 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/12 15:59:45 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*
 *	Tokens:
 *		word			-> 'word'
 *		pipe			-> '|'
 *		redir_in		-> '<'
 *		redir_out		-> '>'
 *		redir_append	-> '>>'
 *		heredoc			-> '<<'
 */
typedef enum e_tokentype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
}	t_token;

/*
 *	Redirections
 *		fname = filename
 */
typedef struct s_redir
{
	t_tokentype		type;
	char			*fname;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

/*
 *	Commands (nodes in pipeline)
 *		av = argc | Null terminated
 *		redirs = redirections | Linked list of redirections
 */
typedef struct s_cmd
{
	char			**av;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/*
 *	Auxiliar structure
 */
typedef struct s_exec_cmds
{
	t_cmd	*cmd;
	int		prev_fd;
	int		pipe_fd[2];
	int		pid;
	int		last_pid;
	int		status;
	int		fd[2];
}	t_exec_cmds;

/*
 *	Function Prototypes
 */
t_token	*tokenize_line(char *line);
t_token	*create_token(t_token **lst, t_tokentype type, char *value);

#endif
