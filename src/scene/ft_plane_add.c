/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:35:10 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 04:01:14 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_plane_setup(t_plane *pl)
{
	t_vec3f const	front = ft_vec3f(0.0F, 0.0F, 1.0F);

	pl->normal = ft_vec3f_unit(pl->normal);
	pl->rotation.xyz = ft_vec3f_cross(front, pl->normal);
	pl->rotation.w = sqrtf(1 + ft_vec3f_dot(front, pl->normal));
	pl->rotation = ft_quat4f_unit(pl->rotation);
	pl->normal = ft_vec3f_unit(ft_vec3f_rotate(front, pl->rotation));
}

bool	ft_plane_add(t_scene *const scene, char *const *info)
{
	t_plane	*pl;
	t_list	*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_09), false);
	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (ft_pstderr(__ERR_07), false);
	new = ft_lstnew(pl);
	if (!new)
		return (ft_pstderr(__ERR_07), free(pl), false);
	pl->point = ft_str_to_vec3f(info[1]);
	if (isnan(pl->point.x))
		return (ft_lstdelone(new, free), false);
	pl->normal = ft_str_to_vec3f(info[2]);
	if (isnan(pl->normal.x) || !ft_vec3f_isnormalized(&pl->normal))
		return (ft_lstdelone(new, free), false);
	pl->color = ft_str_to_color3f(info[3]);
	if (isnan(pl->color.x))
		return (ft_lstdelone(new, free), false);
	ft_plane_setup(pl);
	ft_lstadd_front(&scene->planes, new);
	return (true);
}
