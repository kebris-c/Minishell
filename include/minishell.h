/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:44:22 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/12 16:09:25 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 *	ELIMINAR ESTE DEFINE _XOPEN_... AL SUBIRLO, NO ROMPE NADA, PERO 
 *	ES INNECESARIO. ES PARA ACALLAR LOS WARNINGS DEL LSP DE MI NVIM PORQUE 
 *	ME DA TOC, PERO EN REALIDAD LO DEFINIMOS DENTRO DEL MAKEFILE EN LAS FLAGS,
 *	QUE ES LO CORRECTO.
 */
# define _XOPEN_SOURCE 700

# include "../libft/include/libft.h"

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
 *	External globals. To make extern and accesible global variables
 */
extern volatile sig_atomic_t	g_signal;

/*
 *	env -> env cpy
 *	last_exit -> $? value
 */
typedef struct s_shell
{
	char			**env;
	char			**export_only;
	char			**to_export;
	int				last_exit;
	struct s_shell	*next;
}	t_shell;

/*
 *	Prototype declarations
 */
//	main/
int		minishell_loop(t_shell *sh);

#endif
