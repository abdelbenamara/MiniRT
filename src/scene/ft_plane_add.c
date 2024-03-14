/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:35:10 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:26:29 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_plane_add(t_scene *scene, char **info)
{
	t_plane	*plane;
	t_list	*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	plane = malloc(sizeof(t_plane));
	new = ft_lstnew(plane);
	if (!plane || !new)
		return (ft_pstderr(__ERR_2), free(plane), free(new), 0);
	plane->point = ft_vec3_read(info[1]);
	if (isnanf(plane->point.x))
		return (ft_lstdelone(new, free), 0);
	plane->normal = ft_vec3_read(info[2]);
	if (isnanf(plane->normal.x) || !ft_vec3_is_normalized(plane->normal))
		return (ft_lstdelone(new, free), 0);
	plane->normal = ft_vec3_unit(plane->normal);
	plane->color = ft_color_read(info[3]);
	if (isnanf(plane->color.x))
		return (ft_lstdelone(new, free), 0);
	plane->theta = ft_vec3(0.0F, 0.0F, 0.0F);
	ft_lstadd_front(&scene->planes, new);
	return (1);
}
