/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:19 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 00:27:46 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_cylinder_setup(t_cylinder *const cy, char *const *info)
{
	cy->radius = ft_str_to_float(info[3]);
	if (!isfinite(cy->radius))
		return (ft_pstderr(__ERR_5), false);
	if (signbit(cy->radius))
		return (ft_pstderr(__ERR_14), false);
	cy->height = ft_str_to_float(info[4]);
	if (!isfinite(cy->height))
		return (ft_pstderr(__ERR_5), false);
	if (signbit(cy->height))
		return (ft_pstderr(__ERR_14), false);
	cy->color = ft_str_to_color3f(info[5]);
	if (isnan(cy->color.x))
		return (false);
	cy->axis = ft_vec3f_unit(cy->axis);
	cy->top = ft_vec3f_sum(cy->base, \
		ft_vec3f_prod(cy->axis, cy->height / 2.0F));
	cy->base = ft_vec3f_diff(cy->top, \
		ft_vec3f_prod(cy->axis, cy->height));
	cy->radius *= 0.5F;
	cy->radius_squared = cy->radius * cy->radius;
	cy->radius_reciprocal = 1.0F / cy->radius;
	return (true);
}

bool	ft_cylinder_add(t_scene *const scene, char *const *info)
{
	t_cylinder	*cy;
	t_list		*new;

	if (ft_tab_size(info) != 6)
		return (ft_pstderr(__ERR_4), false);
	cy = malloc(sizeof(t_cylinder));
	new = ft_lstnew(cy);
	if (!cy || !new)
		return (ft_pstderr(__ERR_2), free(cy), free(new), false);
	cy->base = ft_str_to_vec3f(info[1]);
	if (isnan(cy->base.x))
		return (ft_lstdelone(new, free), false);
	cy->axis = ft_str_to_vec3f(info[2]);
	if (isnan(cy->axis.x) || !ft_vec3f_isnormalized(cy->axis))
		return (ft_lstdelone(new, free), false);
	if (!ft_cylinder_setup(cy, info))
		return (ft_lstdelone(new, free), false);
	ft_lstadd_front(&scene->cylinders, new);
	return (true);
}
