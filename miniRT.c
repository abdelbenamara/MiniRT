/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:09:55 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 02:29:03 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_frame_render(t_xclient *const xclient)
{
	int					i;
	int					j;

	if (xclient->update)
	{
		j = 0;
		while (j < _HEIGHT)
		{
			i = 0;
			while (i < _WIDTH)
			{
				ft_pixel_put(xclient, i, j, \
					ft_ray_tracing(xclient->scene, i, j));
				++i;
			}
			++j;
		}
		mlx_clear_window(xclient->mlx, xclient->win);
		mlx_put_image_to_window(xclient->mlx, xclient->win, xclient->img, 0, 0);
		xclient->update = false;
	}
	return (EXIT_SUCCESS);
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
	mlx_hook(xclient->win, \
		DestroyNotify, ButtonReleaseMask, mlx_loop_end, xclient->mlx);
	mlx_hook(xclient->win, KeyPress, KeyPressMask, ft_key_press, xclient);
	mlx_loop_hook(xclient->mlx, ft_frame_render, xclient);
	mlx_loop(xclient->mlx);
	ft_xclient_free(xclient);
	return (EXIT_SUCCESS);
}
