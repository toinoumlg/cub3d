/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:13:01 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 17:38:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// Copies n bytes from memory area src to memory area dest.
// Returns a pointer to dest.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*uc_dest;
	unsigned char	*uc_src;
	size_t			i;

	uc_dest = (unsigned char *)dest;
	uc_src = (unsigned char *)src;
	if (!uc_dest && !uc_src)
		return (NULL);
	if (uc_src < uc_dest)
	{
		i = n;
		while (i-- > 0)
			uc_dest[i] = uc_src[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			uc_dest[i] = uc_src[i];
			i++;
		}
	}
	return ((void *)dest);
}
