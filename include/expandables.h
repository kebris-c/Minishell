/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:30:01 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:30:03 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLES_H
# define EXPANDABLES_H

# include "minishell.h"
# include "tokenizer.h"

typedef struct s_expand
{
	char	*result;
	int		i;
	int		j;
	int		in_squote;
	int		in_dquote;
}	t_expand;

char	*expand_variables(const char *raw, t_shell *sh);
char	*expand_exit_status(char *str, int last_exit);

//env expand
char	*get_env_value(char *key, t_shell *sh);
char	*extract_var_name(char *str, int *i);
int		is_valid_var_char(char c, int first);

//dollar
char	*handle_dollar_sign(char *str, int *i, t_shell *sh);

// quotes
int		handle_quotes(char c, t_expand *exp);
int		should_expand(t_expand *exp);

//string utils
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
char	*ft_strappend_char(char *str, char c);
char	*ft_itoa_custom(int n);

#endif
