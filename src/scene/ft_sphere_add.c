/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:34:18 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:21:56 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_sphere_add(t_scene *scene, char **info)
{
	t_sphere	*sphere;
	t_list		*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	sphere = malloc(sizeof(t_sphere));
	new = ft_lstnew(sphere);
	if (!sphere || !new)
		return (ft_pstderr(__ERR_2), free(sphere), free(new), 0);
	sphere->center = ft_vec3_read(info[1]);
	if (isnanf(sphere->center.x))
		return (ft_lstdelone(new, free), 0);
	sphere->radius = ft_atof(info[2]);
	if (isnanf(sphere->radius))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), 0);
	if (sphere->radius < 0.0F)
		return (ft_pstderr(__ERR_13), ft_lstdelone(new, free), 0);
	sphere->radius *= 0.5F;
	sphere->color = ft_color_read(info[3]);
	if (isnanf(sphere->color.x))
		return (ft_lstdelone(new, free), 0);
	ft_lstadd_front(&scene->spheres, new);
	return (1);
}
