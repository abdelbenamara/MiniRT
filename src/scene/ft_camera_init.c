/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:15 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:24:05 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_camera_init(t_scene *scene, char **info)
{
	if (scene->camera)
		return (ft_pstderr(__ERR_3), 0);
	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (ft_pstderr(__ERR_2), 0);
	scene->camera->position = ft_vec3_read(info[1]);
	if (isnanf(scene->camera->position.x))
		return (0);
	scene->camera->orientation = ft_vec3_read(info[2]);
	if (isnanf(scene->camera->orientation.x)
		|| !ft_vec3_is_normalized(scene->camera->orientation))
		return (0);
	scene->camera->orientation = ft_vec3_unit(scene->camera->orientation);
	scene->camera->fov = ft_atoi(info[3]);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		return (ft_pstderr(__ERR_11), 0);
	scene->camera->theta = ft_vec3(0.0F, 0.0F, 0.0F);
	return (1);
}
