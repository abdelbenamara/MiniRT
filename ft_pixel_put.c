/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:19:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/12/28 18:20:00 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_pixel_put(t_ximage ximage, int x, int y, int color)
{
	char	*pos;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pos = ximage.data + x * (ximage.bpp / 8) + y * ximage.lsize;
	*((unsigned int *) pos) = mlx_get_color_value(ximage.mlx, color);
}
