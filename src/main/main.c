/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:42:20 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/15 16:29:31 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "builtins.h"
#include "utils.h"

/*
 *	Global declaration
 */
volatile sig_atomic_t	g_signal = 0;

/*
 *	init_shell initialize shell structure and use envcpy to copy the enviroment
 */
static char	**envcpy(char **env)
{
	char	**envcpy;
	int		count;
	int		i;

	if (!env || !*env)
		return (NULL);
	count = 0;
	while (env[count])
		count++;
	envcpy = malloc(sizeof(char *) * (count + 1));
	if (!envcpy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envcpy[i] = ft_strdup(env[i]);
		if (!envcpy[i])
			return (ft_free_matrix(envcpy), NULL);
		i++;
	}
	envcpy[i] = NULL;
	return (envcpy);
}

static t_shell	*init_shell(char **env)
{
	t_shell	*sh;

	sh = malloc(sizeof(*sh));
	if (!sh)
		return (NULL);
	sh->env = envcpy(env);
	sh->export_only = NULL;
	sh->to_export = NULL;
	sh->last_exit = 0;
	return (sh);
}

/*
 *	We need to declare as void ac and av in purpose of get env
 */
int	main(int ac, char **av, char **env)
{
	t_shell	*sh;
	int		status;

	if (ac != 1)
	{
		printf("Current minishell version does not handle parameters\n");
		return (127);
	}
	(void)av;
	sh = init_shell(env);
	if (!sh)
		return (1);
	setup_prompt_signals();
	status = minishell_loop(sh);
	shred_program(sh);
	exit(status);
	return (status);
}
