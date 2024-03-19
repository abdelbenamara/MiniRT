/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:46:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/18 14:22:45 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_sphere_hit(t_sphere *sp, t_ray r, t_hit *h)
{
	const t_vec3	oc = ft_vec3_diff(sp->center, r.origin);
	const float		nb = ft_vec3_dot(oc, r.direction);
	const float		c = ft_vec3_dot(oc, oc) - sp->radius_squared;
	float			d;
	float			t;

	if (!isfinite(nb) || !isfinite(c) || (signbit(nb) && c >= 0.0F))
		return ;
	d = powf(nb, 2.0F) - c;
	if (!isfinite(d) || signbit(d))
		return ;
	if (c >= 0.0F)
		t = nb - sqrtf(d);
	else
		t = nb + sqrtf(d);
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	h->t = t;
	h->point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, h->t));
	h->normal = ft_face_normal(r.direction, ft_vec3_prod(\
		ft_vec3_diff(h->point, sp->center), sp->radius_reciprocal));
	h->color = sp->color;
}
