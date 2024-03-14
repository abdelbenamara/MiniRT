/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:19:40 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/08 00:15:41 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_pixel_put(t_xclient *xclient, int x, int y, int color)
{
	char	*pos;

	if (x < 0 || x >= _WIDTH || y < 0 || y >= _HEIGHT)
		return ;
	pos = xclient->data + x * (xclient->bpp / 8) + y * xclient->lsize;
	*((unsigned int *) pos) = mlx_get_color_value(xclient->mlx, color);
}
