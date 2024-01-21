/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:21:54 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/21 19:09:01 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_xclient	*ft_xclient_new(t_scene *scene)
{
	t_xclient	*xclient;

	xclient = malloc(sizeof(t_xclient));
	if (!xclient)
		return (ft_scene_free(scene), NULL);
	xclient->mlx = mlx_init();
	xclient->win = NULL;
	xclient->scene = scene;
	if (!xclient->mlx)
		return (ft_xclient_free(xclient), NULL);
	xclient->win = mlx_new_window(xclient->mlx, __WIDTH, __HEIGHT, __TITLE);
	if (!xclient->win)
		return (ft_xclient_free(xclient), NULL);
	return (xclient);
}
