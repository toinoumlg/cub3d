/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:02:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 17:57:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// Outputs 'c' to the given 'fd'.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
