/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:55:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 17:54:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

// Returns a pointer to last occurrence of character c in string s.
// Return NULL if c is not found.
char	*ft_strrchr(const char *s, int c)
{
	int		len_s;
	char	*c_s;
	char	c_c;

	c_c = c;
	c_s = (char *)s;
	len_s = ft_strlen(c_s);
	while (len_s >= 0)
	{
		if (c_s[len_s] == c_c)
			return (c_s + len_s);
		len_s--;
	}
	return (0);
}
