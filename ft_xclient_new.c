/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:21:54 by abenamar          #+#    #+#             */
/*   Updated: 2023/12/30 23:25:24 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_xclient	*ft_xclient_new(t_scene *scene)
{
	t_xclient	*xclient;

	xclient = malloc(sizeof(t_xclient));
	if (!xclient)
		return (NULL);
	xclient->mlx = NULL;
	xclient->win = NULL;
	xclient->ximage.img = NULL;
	xclient->xsettings.scene = scene;
	ft_xsettings_reset(&xclient->xsettings);
	xclient->mlx = mlx_init();
	if (!(xclient->mlx))
		return (ft_xclient_free(xclient), NULL);
	xclient->win = mlx_new_window(xclient->mlx, WIDTH, HEIGHT, TITLE);
	if (!(xclient->win))
		return (ft_xclient_free(xclient), NULL);
	xclient->ximage = ft_ximage_init(xclient);
	if (!(xclient->ximage.img))
		return (ft_xclient_free(xclient), NULL);
	return (xclient);
}
