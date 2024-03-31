/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:46:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/01 01:14:21 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_sphere_hit(t_sphere *const sp, t_ray const r, t_hit *const h)
{
	t_vec3f const	oc = ft_vec3f_diff(sp->center, r.origin);
	float const		nb = ft_vec3f_dot(oc, r.direction);
	float const		c = ft_vec3f_dot(oc, oc) - sp->radius_squared;
	float			d;
	float			t;

	if (!isfinite(nb) || !isfinite(c) || (signbit(nb) && c >= 0.0F))
		return ;
	d = nb * nb - c;
	if (!isfinite(d) || signbit(d))
		return ;
	if (c >= 0.0F)
		t = nb - sqrtf(d);
	else
		t = nb + sqrtf(d);
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	h->t = t;
	h->point = ft_vec3f_sum(r.origin, ft_vec3f_prod(r.direction, h->t));
	h->normal = ft_face_normal(r.direction, ft_vec3f_prod(\
		ft_vec3f_diff(h->point, sp->center), sp->radius_reciprocal));
	h->color = sp->color;
}
