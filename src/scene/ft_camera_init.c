/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:15 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 13:46:55 by abenamar         ###   ########.fr       */
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
		return (ft_pstderr(__ERR_07), false);
	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_08), false);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (ft_pstderr(__ERR_06), false);
	scene->camera->position = ft_str_to_vec3f(info[1]);
	if (isnan(scene->camera->position.x))
		return (false);
	scene->camera->orientation = ft_str_to_vec3f(info[2]);
	if (isnan(scene->camera->orientation.x)
		|| !ft_vec3f_isnormalized(&scene->camera->orientation))
		return (false);
	scene->camera->fov = ft_str_to_float(info[3]);
	if (!isfinite(scene->camera->fov))
		return (ft_pstderr(__ERR_09), false);
	if (signbit(scene->camera->fov) || scene->camera->fov > 180.0F)
		return (ft_pstderr(__ERR_16), false);
	scene->camera->fov *= __M_PIF / 180.0F;
	if (scene->camera->fov > __M_PIF - FLT_EPSILON)
		scene->camera->fov = __M_PIF - FLT_EPSILON;
	ft_camera_setup(scene->camera);
	return (true);
}
