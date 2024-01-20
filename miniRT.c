/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:09:55 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 15:27:36 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	mlx_hook(xclient->win, \
		KeyPress, KeyPressMask, ft_key_press_handle, xclient);
	mlx_loop_hook(xclient->mlx, ft_frame_render, xclient);
	mlx_loop(xclient->mlx);
	return (ft_xclient_free(xclient), 0);
}
