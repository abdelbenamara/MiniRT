/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:09:55 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/29 01:16:27 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_frame_render(t_xclient *xclient)
{
	if (xclient->update)
	{
		ft_ray_tracing(xclient);
		mlx_clear_window(xclient->mlx, xclient->win);
		mlx_put_image_to_window(xclient->mlx, xclient->win, xclient->img, 0, 0);
		xclient->update = 0;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char		*fext;
	t_scene		*scene;
	t_xclient	*xclient;

	if (ac < 2)
		return (ft_pstderr(__USAGE), 2);
	fext = ft_strrchr(av[1], '.');
	if (!fext || ft_strncmp(fext, ".rt", 4))
		return (ft_pstderr(__ERR_1), EXIT_FAILURE);
	scene = ft_scene_new(av[1]);
	if (!scene)
		return (1);
	xclient = ft_xclient_new(scene);
	if (!xclient)
		return (1);
	mlx_hook(xclient->win, DestroyNotify, ButtonReleaseMask, \
		mlx_loop_end, xclient->mlx);
	mlx_hook(xclient->win, KeyPress, KeyPressMask, \
		ft_key_press, xclient);
	mlx_loop_hook(xclient->mlx, ft_frame_render, xclient);
	mlx_loop(xclient->mlx);
	return (ft_xclient_free(xclient), EXIT_SUCCESS);
}
