/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:15 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/02 23:52:34 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_camera_setup(t_camera *const camera)
{
	t_vec3f const	front = ft_vec3f(0.0F, 0.0F, 1.0F);

	camera->orientation = ft_vec3f_unit(camera->orientation);
	camera->rotation.xyz = ft_vec3f_cross(front, camera->orientation);
	camera->rotation.w = sqrtf(1 + ft_vec3f_dot(front, camera->orientation));
	camera->rotation = ft_quat4f_unit(camera->rotation);
	camera->vup = ft_vec3f_unit(\
		ft_vec3f_rotate(ft_vec3f(0.0F, 1.0F, 0.0F), camera->rotation));
	camera->orientation = ft_vec3f_unit(\
		ft_vec3f_rotate(front, camera->rotation));
}

bool	ft_camera_init(t_scene *const scene, char *const *info)
{
	if (scene->camera)
		return (ft_pstderr(__ERR_3), false);
	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), false);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (ft_pstderr(__ERR_2), false);
	scene->camera->position = ft_str_to_vec3f(info[1]);
	if (isnan(scene->camera->position.x))
		return (false);
	scene->camera->orientation = ft_str_to_vec3f(info[2]);
	if (isnan(scene->camera->orientation.x)
		|| !ft_vec3f_isnormalized(scene->camera->orientation))
		return (false);
	scene->camera->fov = __M_PIF / 180.0F * ft_atoi(info[3]);
	if (signbit(scene->camera->fov) || scene->camera->fov > __M_PIF)
		return (ft_pstderr(__ERR_12), false);
	if (scene->camera->fov > __M_PIF - FLT_EPSILON)
		scene->camera->fov = __M_PIF - FLT_EPSILON;
	ft_camera_setup(scene->camera);
	return (true);
}
