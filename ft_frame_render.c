/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:51 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/22 00:40:07 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_ximage	ft_ximage_init(t_xclient *xclient)
{
	t_ximage	ximage;

	ximage.mlx = xclient->mlx;
	ximage.img = mlx_new_image(ximage.mlx, __WIDTH, __HEIGHT);
	if (!ximage.img)
		(ft_xclient_free(xclient), exit(EXIT_FAILURE));
	ximage.data = mlx_get_data_addr(\
		ximage.img, &ximage.bpp, &ximage.lsize, &ximage.endian);
	ximage.scene = xclient->scene;
	return (ximage);
}

static void	ft_ximage_draw(t_ximage ximage)
{
	t_vec3	a;
	t_vec2	b;

	a.x = __WIDTH / 2.0;
	a.y = __HEIGHT / 2.0;
	a.z = 0.0;
	b = ft_perspective_projection(a, \
		ximage.scene->camera->position, ximage.scene->camera->orientation);
	ft_pixel_put(ximage, b.x, b.y, 0x00FF0000);
}

int	ft_frame_render(t_xclient *xclient)
{
	t_ximage	ximage;

	ximage = ft_ximage_init(xclient);
	ft_ximage_draw(ximage);
	mlx_clear_window(xclient->mlx, xclient->win);
	mlx_put_image_to_window(xclient->mlx, xclient->win, ximage.img, 0, 0);
	mlx_destroy_image(xclient->mlx, ximage.img);
	return (0);
}
