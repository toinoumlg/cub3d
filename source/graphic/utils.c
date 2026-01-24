/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:29:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 01:02:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_pxl	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}
