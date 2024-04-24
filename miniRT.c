/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:09:55 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 04:01:14 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_program_isvalid(char const *filename)
{
	int const	inum[] = {_WIDTH, _HEIGHT, _SAMPLES_PER_PIXEL, _MAX_DEPTH};
	float const	fnum = _SHADOW_BIAS;
	char		*extension;

	if (inum[0] <= 0)
		return (ft_pstderr(__ERR_01), false);
	if (inum[1] <= 0)
		return (ft_pstderr(__ERR_02), false);
	if (inum[2] <= 0)
		return (ft_pstderr(__ERR_03), false);
	if (inum[3] < 0)
		return (ft_pstderr(__ERR_04), false);
	if (signbit(fnum))
		return (ft_pstderr(__ERR_05), false);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".rt", 4))
		return (ft_pstderr(__ERR_07), false);
	return (true);
}

static int	ft_frame_render(t_xclient *const xclient)
{
	int	i;
	int	j;

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
		mlx_put_image_to_window(xclient->mlx, xclient->win, xclient->img, 0, 0);
		xclient->update = false;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_scene		*scene;
	t_xclient	*xclient;

	if (ac < 2)
		return (ft_pstderr(__USAGE), 2);
	if (!ft_program_isvalid(av[1]))
		return (EXIT_FAILURE);
	scene = ft_scene_new(av[1]);
	if (!scene)
		return (EXIT_FAILURE);
	xclient = ft_xclient_new(scene);
	if (!xclient)
		return (EXIT_FAILURE);
	mlx_hook(xclient->win, \
		DestroyNotify, ButtonReleaseMask, mlx_loop_end, xclient->mlx);
	mlx_hook(xclient->win, KeyPress, KeyPressMask, ft_key_press, xclient);
	mlx_loop_hook(xclient->mlx, ft_frame_render, xclient);
	mlx_loop(xclient->mlx);
	ft_xclient_free(xclient);
	return (EXIT_SUCCESS);
}
