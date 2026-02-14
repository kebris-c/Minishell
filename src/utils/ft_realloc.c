/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:25:43 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/29 19:33:47 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (old_size < new_size)
		ft_memcpy(new, ptr, old_size);
	else
		ft_memcpy(new, ptr, new_size);
	free(ptr);
	return (new);
}
