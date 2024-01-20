/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:38:07 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 17:13:20 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_camera_init(t_scene *scene, char **info)
{
	t_vec3	*u;

	if (scene->camera)
		return (ft_pstderr(__ERR_3), 0);
	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (ft_pstderr(__ERR_2), 0);
	u = ft_vec3_init(info[1]);
	if (!u)
		return (0);
	scene->camera->position = *u;
	(free(u), u = ft_vec3_init(info[2]));
	if (!u)
		return (0);
	scene->camera->orientation = *u;
	if (u->x < -1.0 || u->y < -1.0 || u->z < -1.0
		|| u->x > 1.0 || u->y > 1.0 || u->z > 1.0)
		return (ft_pstderr(__ERR_10), free(u), 0);
	free(u);
	scene->camera->fov = ft_atoi(info[3]);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		return (ft_pstderr(__ERR_11), 0);
	return (1);
}
