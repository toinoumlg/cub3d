/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:59:15 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 18:26:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks whether c fits into the ASCII character set.
// Returns: 0 if false; 1 if true.
int	ft_isascii(int c)
{
	if (c >= 0 && c < 128)
		return (1);
	return (0);
}
