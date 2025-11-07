/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:47:52 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 17:47:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>

// Returns the length of the string s, excluding \0.
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
