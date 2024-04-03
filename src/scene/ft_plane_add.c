/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:35:10 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/02 23:52:34 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_plane_add(t_scene *const scene, char *const *info)
{
	t_plane	*pl;
	t_list	*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), false);
	pl = malloc(sizeof(t_plane));
	new = ft_lstnew(pl);
	if (!pl || !new)
		return (ft_pstderr(__ERR_2), free(pl), free(new), false);
	pl->point = ft_str_to_vec3f(info[1]);
	if (isnan(pl->point.x))
		return (ft_lstdelone(new, free), false);
	pl->normal = ft_str_to_vec3f(info[2]);
	if (isnan(pl->normal.x) || !ft_vec3f_isnormalized(pl->normal))
		return (ft_lstdelone(new, free), false);
	pl->color = ft_str_to_color3f(info[3]);
	if (isnan(pl->color.x))
		return (ft_lstdelone(new, free), false);
	pl->normal = ft_vec3f_unit(pl->normal);
	ft_lstadd_front(&scene->planes, new);
	return (true);
}
