/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:26:22 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:26:24 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	count_unquoted_len(char *str)
{
	int		i;
	int		len;
	int		in_quote;
	char	quote_char;

	i = 0;
	len = 0;
	in_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (!in_quote && is_quote(str[i]))
		{
			in_quote = 1;
			quote_char = str[i];
		}
		else if (in_quote && str[i] == quote_char)
			in_quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}

static void	copy_unquoted(char *dest, char *src)
{
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (src[i])
	{
		if (!in_quote && is_quote(src[i]))
		{
			in_quote = 1;
			quote_char = src[i];
		}
		else if (in_quote && src[i] == quote_char)
			in_quote = 0;
		else
			dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
}

char	*remove_quotes(char *str)
{
	char	*unquoted;
	int		len;

	if (!str)
		return (NULL);
	len = count_unquoted_len(str);
	unquoted = malloc(sizeof(char) * (len + 1));
	if (!unquoted)
		return (NULL);
	copy_unquoted(unquoted, str);
	return (unquoted);
}

static char	*process_export_value(char *str)
{
	char	*key;
	char	*value;
	char	*unquoted_value;
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(str));
	key = extract_key(str);
	if (!key)
		return (NULL);
	value = str + i + 1;
	unquoted_value = remove_quotes(value);
	if (!unquoted_value)
	{
		free(key);
		return (NULL);
	}
	result = ft_strjoin_three(key, "=", unquoted_value);
	free(key);
	free(unquoted_value);
	return (result);
}

char	*export_string(char *str)
{
	if (!assigned_value(str))
		return (ft_strdup(str));
	return (process_export_value(str));
}
