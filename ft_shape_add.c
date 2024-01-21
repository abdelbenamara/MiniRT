/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shape_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:08:10 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/21 20:19:57 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_sphere_add(t_scene *scene, char **info)
{
	t_sphere	*sphere;
	t_list		*new;
	t_vec3		*u;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	sphere = malloc(sizeof(t_sphere));
	new = ft_lstnew(sphere);
	if (!sphere || !new)
		return (ft_pstderr(__ERR_2), free(sphere), free(new), 0);
	u = ft_vec3_new(info[1]);
	if (!u)
		return (ft_lstdelone(new, free), 0);
	sphere->center = *u;
	free(u);
	sphere->diameter = ft_atof(info[2]);
	if (isnan(sphere->diameter))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), 0);
	if (sphere->diameter < 0.0)
		return (ft_pstderr(__ERR_13), ft_lstdelone(new, free), 0);
	sphere->color = ft_color_value(info[3]);
	if (sphere->color == -1)
		return (ft_lstdelone(new, free), 0);
	ft_lstadd_front(&scene->spheres, new);
	return (1);
}

static uint8_t	ft_plane_add(t_scene *scene, char **info)
{
	t_plane	*plane;
	t_list	*new;
	t_vec3	*u;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	plane = malloc(sizeof(t_plane));
	new = ft_lstnew(plane);
	if (!plane || !new)
		return (ft_pstderr(__ERR_2), free(plane), free(new), 0);
	u = ft_vec3_new(info[1]);
	if (!u)
		return (ft_lstdelone(new, free), 0);
	plane->point = *u;
	(free(u), u = ft_vec3_new(info[2]));
	if (!u)
		return (ft_lstdelone(new, free), 0);
	plane->orientation = *u;
	if (u->x < -1.0 || u->y < -1.0 || u->z < -1.0
		|| u->x > 1.0 || u->y > 1.0 || u->z > 1.0)
		return (ft_pstderr(__ERR_10), free(u), ft_lstdelone(new, free), 0);
	(free(u), plane->color = ft_color_value(info[3]));
	if (plane->color == -1)
		return (ft_lstdelone(new, free), 0);
	return (ft_lstadd_front(&scene->planes, new), 1);
}

static uint8_t	ft_cylinder_add(t_scene *scene, char **info)
{
	t_cylinder	*cylinder;
	t_list		*new;
	t_vec3		*u;

	if (ft_tab_size(info) != 6)
		return (ft_pstderr(__ERR_4), 0);
	cylinder = malloc(sizeof(t_cylinder));
	new = ft_lstnew(cylinder);
	if (!cylinder || !new)
		return (ft_pstderr(__ERR_2), free(cylinder), free(new), 0);
	u = ft_vec3_new(info[1]);
	if (!u)
		return (ft_lstdelone(new, free), 0);
	cylinder->center = *u;
	(free(u), u = ft_vec3_new(info[2]));
	if (!u)
		return (ft_lstdelone(new, free), 0);
	cylinder->orientation = *u;
	if (u->x < -1.0 || u->y < -1.0 || u->z < -1.0
		|| u->x > 1.0 || u->y > 1.0 || u->z > 1.0)
		return (ft_pstderr(__ERR_10), free(u), ft_lstdelone(new, free), 0);
	(free(u), cylinder->color = ft_color_value(info[5]));
	if (cylinder->color == -1)
		return (ft_lstdelone(new, free), 0);
	return (ft_lstadd_front(&scene->cylinders, new), 1);
}

uint8_t	ft_shape_add(t_scene *scene, char **info)
{
	static uint8_t	(*ft_item_add[])(t_scene *, char **) = {
		ft_sphere_add, ft_plane_add, ft_cylinder_add
	};
	const int		n = !ft_strncmp(info[0], "sp", 3) \
						+ 2 * !ft_strncmp(info[0], "pl", 3) \
						+ 3 * !ft_strncmp(info[0], "cy", 3);
	t_cylinder		*cylinder;

	if (!n)
		return (ft_pstderr(__ERR_12), 0);
	if (!ft_item_add[n - 1](scene, info))
		return (0);
	if (n == 3)
	{
		cylinder = scene->cylinders->content;
		cylinder->diameter = ft_atof(info[3]);
		cylinder->height = ft_atof(info[4]);
		if (isnan(cylinder->diameter) || isnan(cylinder->height))
			return (ft_pstderr(__ERR_5), 0);
		if (cylinder->diameter < 0.0 || cylinder->height < 0.0)
			return (ft_pstderr(__ERR_13), 0);
	}
	return (1);
}
