/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:20 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:56:39 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_cylinder_hit(t_cylinder *cy, t_ray r, t_hit *h)
{
	const t_vec3	oc = ft_vec3_diff(r.origin, cy->center);
	const float		dx = ft_vec3_dot(r.direction, cy->axis);
	const float		xv = ft_vec3_dot(oc, cy->axis);
	const t_vec3	abc = ft_vec3(\
		ft_vec3_dot(r.direction, r.direction) - powf(dx, 2.0F), \
		2 * (ft_vec3_dot(r.direction, oc) - dx * xv), \
		ft_vec3_dot(oc, oc) - powf(xv, 2.0F) - powf(cy->radius, 2.0F));
	const float		d = abc.y * abc.y - 4 * abc.x * abc.z;
	float			sd;
	float			t;

	if (d < 0.0F)
		return ;
	sd = sqrtf(d);
	t = (-abc.y - sd) / 2 * abc.x;
	if (t < FLT_EPSILON || h->t < t)
	{
		t = (-abc.y + sd) / 2 * abc.x;
		if (t < FLT_EPSILON || h->t < t)
			return ;
	}
	h->t = t;
	h->point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, h->t));
	h->normal = ft_vec3(nanf(""), nanf(""), nanf(""));
	h->color = cy->color;
}
