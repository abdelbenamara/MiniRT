/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:19 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 13:41:57 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_cylinder_setup(t_cylinder *const cy, char *const *info)
{
	t_vec3f const	front = ft_vec3f(0.0F, 0.0F, 1.0F);

	cy->radius.twice = ft_str_to_float(info[3]);
	if (!isfinite(cy->radius.twice))
		return (ft_pstderr(__ERR_09), false);
	if (signbit(cy->radius.twice))
		return (ft_pstderr(__ERR_18), false);
	cy->arrow.height = ft_str_to_float(info[4]);
	if (!isfinite(cy->arrow.height))
		return (ft_pstderr(__ERR_09), false);
	if (signbit(cy->arrow.height))
		return (ft_pstderr(__ERR_18), false);
	cy->color = ft_str_to_color3f(info[5]);
	if (isnan(cy->color.x))
		return (false);
	cy->axis = ft_vec3f_unit(cy->axis);
	cy->rotation.xyz = ft_vec3f_cross(front, cy->axis);
	cy->rotation.w = sqrtf(1 + ft_vec3f_dot(front, cy->axis));
	cy->rotation = ft_quat4f_unit(cy->rotation);
	cy->axis = ft_vec3f_unit(ft_vec3f_rotate(front, cy->rotation));
	cy->arrow = ft_arrow(cy->arrow.center, cy->axis, cy->arrow.height);
	cy->radius = ft_radius(cy->radius.twice);
	return (true);
}

bool	ft_cylinder_add(t_scene *const scene, char *const *info)
{
	t_cylinder	*cy;
	t_list		*new;

	if (ft_tab_size(info) != 6)
		return (ft_pstderr(__ERR_08), false);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		return (ft_pstderr(__ERR_06), false);
	new = ft_lstnew(cy);
	if (!new)
		return (ft_pstderr(__ERR_06), free(cy), false);
	cy->arrow.center = ft_str_to_vec3f(info[1]);
	if (isnan(cy->arrow.center.x))
		return (ft_lstdelone(new, free), false);
	cy->axis = ft_str_to_vec3f(info[2]);
	if (isnan(cy->axis.x) || !ft_vec3f_isnormalized(&cy->axis))
		return (ft_lstdelone(new, free), false);
	if (!ft_cylinder_setup(cy, info))
		return (ft_lstdelone(new, free), false);
	ft_lstadd_front(&scene->cylinders, new);
	return (true);
}
