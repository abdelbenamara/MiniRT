/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ximage_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:22:19 by abenamar          #+#    #+#             */
/*   Updated: 2023/12/30 22:56:44 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ximage	ft_ximage_init(t_xclient *xclient)
{
	t_ximage	ximage;

	ximage.mlx = xclient->mlx;
	ximage.img = mlx_new_image(ximage.mlx, WIDTH, HEIGHT);
	if (!(ximage.img))
		(ft_xclient_free(xclient), exit(EXIT_FAILURE));
	ximage.data = mlx_get_data_addr(ximage.img, \
		&(ximage.bpp), &(ximage.lsize), &(ximage.endian));
	ximage.xsettings = xclient->xsettings;
	return (ximage);
}
