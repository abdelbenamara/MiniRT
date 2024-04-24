/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:21:54 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 13:35:03 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_xclient	*ft_xclient_new(t_scene *const scene)
{
	t_xclient	*xclient;

	xclient = malloc(sizeof(t_xclient));
	if (!xclient)
		return (ft_pstderr(__ERR_06), ft_scene_free(scene), NULL);
	xclient->mlx = mlx_init();
	xclient->win = NULL;
	xclient->img = NULL;
	xclient->update = true;
	xclient->scene = scene;
	if (!xclient->mlx)
		return (ft_pstderr(__ERR_06), ft_xclient_free(xclient), NULL);
	xclient->win = mlx_new_window(xclient->mlx, _WIDTH, _HEIGHT, _TITLE);
	if (!xclient->win)
		return (ft_pstderr(__ERR_06), ft_xclient_free(xclient), NULL);
	xclient->img = mlx_new_image(xclient->mlx, _WIDTH, _HEIGHT);
	if (!xclient->img)
		return (ft_pstderr(__ERR_06), ft_xclient_free(xclient), NULL);
	xclient->data = mlx_get_data_addr(\
		xclient->img, &xclient->bpp, &xclient->lsize, &xclient->endian);
	return (xclient);
}
