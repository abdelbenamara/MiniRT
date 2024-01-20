/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:51 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 17:32:08 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_frame_render(t_xclient *xclient)
{
	t_ximage	xbuffer;
	void		*oldimg;

	xbuffer = ft_ximage_init(xclient);
	if (!(xbuffer.img))
		return (EXIT_FAILURE);
	oldimg = xclient->ximage.img;
	xclient->ximage = xbuffer;
	mlx_destroy_image(xclient->mlx, oldimg);
	mlx_clear_window(xclient->mlx, xclient->win);
	mlx_put_image_to_window(xclient->mlx, \
		xclient->win, xclient->ximage.img, 0, 0);
	return (EXIT_SUCCESS);
}
