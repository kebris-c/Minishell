/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:34:26 by kebris-c          #+#    #+#             */
/*   Updated: 2026/02/11 17:51:19 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "tokenizer.h"

typedef enum e_builtintype
{
	B_NOT_BUILTIN,
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}	t_builtintype;

//Builtins functions
int		cd_built(t_cmd *cmd, t_shell *sh);
int		echo_built(t_cmd *cmd);
int		env_built(t_cmd *cmd, t_shell *sh);
int		exit_built(t_cmd *cmd, t_shell *sh);
int		export_built(t_cmd *cmd, t_shell *sh);
int		pwd_built(t_cmd *cmd, t_shell *sh);
int		unset_built(t_cmd *cmd, t_shell *sh);

//Execute builtins
int		exec_builtin(t_cmd *cmd, t_shell *sh, t_builtintype builtin);

//Helper functions
void	free_array(char **arr, int count);
int		is_quote(char c);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
int		is_builtin(char *cmd);
int		array_length(char **arr);
void	process_export_arg(t_cmd *cmd, t_shell *sh, int *i);
int		is_quote(char c);

//Export helpers
void	bubble_sort(char **arr);
char	**get_key(t_shell *sh);
void	match_key_value(t_shell *sh);
char	*export_string(char *str);
int		env_update(t_shell *sh, char *str, char *key);
int		assigned_value(char *str);
char	*extract_key(char *str);
int		key_matches(char *env_var, char *key);
char	**add_to_env(t_shell *sh, char *str);
int		check_valid_key(char *key);
char	**add_to_export_only(t_shell *sh, char *str);
#endif
