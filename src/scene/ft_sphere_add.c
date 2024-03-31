/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:34:18 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/30 18:06:27 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_sphere_add(t_scene *const scene, char *const *info)
{
	t_sphere	*sp;
	t_list		*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), false);
	sp = malloc(sizeof(t_sphere));
	new = ft_lstnew(sp);
	if (!sp || !new)
		return (ft_pstderr(__ERR_2), free(sp), free(new), false);
	sp->center = ft_vec3f_read(info[1]);
	if (isnan(sp->center.x))
		return (ft_lstdelone(new, free), false);
	sp->radius = ft_atof(info[2]);
	if (isnan(sp->radius))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), false);
	if (signbit(sp->radius))
		return (ft_pstderr(__ERR_13), ft_lstdelone(new, free), false);
	sp->color = ft_color3f_read(info[3]);
	if (isnan(sp->color.x))
		return (ft_lstdelone(new, free), false);
	sp->radius *= 0.5F;
	sp->radius_squared = sp->radius * sp->radius;
	sp->radius_reciprocal = 1.0F / sp->radius;
	ft_lstadd_front(&scene->spheres, new);
	return (true);
}
