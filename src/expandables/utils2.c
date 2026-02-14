/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:29:11 by lkoualla          #+#    #+#             */
/*   Updated: 2026/02/11 15:29:13 by lkoualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandables.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	handle_negative(long *nb, char *str)
{
	if (*nb < 0)
	{
		str[0] = '-';
		*nb = -*nb;
	}
}

static void	ft_putnbr_str(int n, char *str, int len)
{
	long	nb;

	nb = n;
	str[len] = '\0';
	handle_negative(&nb, str);
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa_custom(int n)
{
	char	*str;
	int		len;

	len = ft_numlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_putnbr_str(n, str, len);
	return (str);
}
