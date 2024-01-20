/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:21:34 by abenamar          #+#    #+#             */
/*   Updated: 2023/12/30 22:58:25 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_xclient_free(t_xclient *xclient)
{
	ft_scene_free(xclient->xsettings.scene);
	if (xclient->ximage.img)
		mlx_destroy_image(xclient->mlx, xclient->ximage.img);
	if (xclient->win)
		mlx_destroy_window(xclient->mlx, xclient->win);
	if (xclient->mlx)
		(mlx_destroy_display(xclient->mlx), free(xclient->mlx));
	free(xclient);
}
