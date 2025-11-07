/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:15:01 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 17:37:57 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

// Fills first n bytes of memory area pointed by s with constant byte c.
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*uc_s;

	i = 0;
	uc_s = (unsigned char *)s;
	while (i < n)
	{
		uc_s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
