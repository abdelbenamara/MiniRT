/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:19 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:41:13 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_cylinder_setup(t_cylinder *cylinder, char **info)
{
	cylinder->radius = ft_atof(info[3]);
	if (isnanf(cylinder->radius))
		return (ft_pstderr(__ERR_5), 0);
	if (cylinder->radius < 0.0F)
		return (ft_pstderr(__ERR_13), 0);
	cylinder->radius *= 0.5F;
	cylinder->height = ft_atof(info[4]);
	if (isnanf(cylinder->height))
		return (ft_pstderr(__ERR_5), 0);
	if (cylinder->height < 0.0F)
		return (ft_pstderr(__ERR_13), 0);
	return (1);
}

uint8_t	ft_cylinder_add(t_scene *scene, char **info)
{
	t_cylinder	*cylinder;
	t_list		*new;

	if (ft_tab_size(info) != 6)
		return (ft_pstderr(__ERR_4), 0);
	cylinder = malloc(sizeof(t_cylinder));
	new = ft_lstnew(cylinder);
	if (!cylinder || !new)
		return (ft_pstderr(__ERR_2), free(cylinder), free(new), 0);
	cylinder->center = ft_vec3_read(info[1]);
	if (isnanf(cylinder->center.x))
		return (ft_lstdelone(new, free), 0);
	cylinder->axis = ft_vec3_read(info[2]);
	if (isnanf(cylinder->axis.x) || !ft_vec3_is_normalized(cylinder->axis))
		return (ft_lstdelone(new, free), 0);
	cylinder->axis = ft_vec3_unit(cylinder->axis);
	cylinder->color = ft_color_read(info[5]);
	if (isnanf(cylinder->color.x))
		return (ft_lstdelone(new, free), 0);
	if (!ft_cylinder_setup(cylinder, info))
		return (ft_lstdelone(new, free), 0);
	cylinder->theta = ft_vec3(0.0F, 0.0F, 0.0F);
	ft_lstadd_front(&scene->cylinders, new);
	return (1);
}
