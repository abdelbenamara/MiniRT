/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:19 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/18 13:58:44 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_cylinder_setup(t_cylinder *cy, char **info)
{
	cy->radius = ft_atof(info[3]);
	if (isnan(cy->radius))
		return (ft_pstderr(__ERR_5), false);
	if (cy->radius < 0.0F)
		return (ft_pstderr(__ERR_13), false);
	cy->height = ft_atof(info[4]);
	if (isnan(cy->height))
		return (ft_pstderr(__ERR_5), false);
	if (cy->height < 0.0F)
		return (ft_pstderr(__ERR_13), false);
	cy->color = ft_color_read(info[5]);
	if (isnan(cy->color.x))
		return (false);
	cy->axis = ft_vec3_unit(cy->axis);
	cy->top = ft_vec3_sum(cy->base, ft_vec3_prod(cy->axis, cy->height / 2.0F));
	cy->base = ft_vec3_diff(cy->top, ft_vec3_prod(cy->axis, cy->height));
	cy->radius *= 0.5F;
	cy->radius_squared = powf(cy->radius, 2.0F);
	cy->radius_reciprocal = 1.0F / cy->radius;
	cy->theta = ft_vec3(0.0F, 0.0F, 0.0F);
	return (true);
}

bool	ft_cylinder_add(t_scene *scene, char **info)
{
	t_cylinder	*cy;
	t_list		*new;

	if (ft_tab_size(info) != 6)
		return (ft_pstderr(__ERR_4), false);
	cy = malloc(sizeof(t_cylinder));
	new = ft_lstnew(cy);
	if (!cy || !new)
		return (ft_pstderr(__ERR_2), free(cy), free(new), false);
	cy->base = ft_vec3_read(info[1]);
	if (isnan(cy->base.x))
		return (ft_lstdelone(new, free), false);
	cy->axis = ft_vec3_read(info[2]);
	if (isnan(cy->axis.x) || !ft_vec3_is_normalized(cy->axis))
		return (ft_lstdelone(new, free), false);
	if (!ft_cylinder_setup(cy, info))
		return (ft_lstdelone(new, free), false);
	ft_lstadd_front(&scene->cylinders, new);
	return (true);
}
