/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:46:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/27 13:35:25 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void
	ft_sphere_hit(t_sphere const *const sp, \
		t_ray const *const r, t_hit *const h)
{
	t_vec3f const	oc = ft_vec3f_diff(sp->center, r->origin);
	float const		nb = ft_vec3f_dot(oc, r->direction);
	float const		c = ft_vec3f_dot(oc, oc) - sp->radius.square;
	float			d;
	float			t;

	if (!isfinite(nb) || !isfinite(c) || (signbit(nb) && c >= h->bias))
		return ;
	d = powf(nb, 2.0F) - c;
	if (!isfinite(d) || signbit(d))
		return ;
	if (c >= h->bias)
		t = nb - sqrtf(d);
	else
		t = nb + sqrtf(d);
	if (!isfinite(t) || signbit(t) || h->bias >= t || t >= h->t)
		return ;
	h->t = t;
	h->point = ft_vec3f_sum(r->origin, ft_vec3f_prod(r->direction, h->t));
	h->normal = ft_face_normal(r->direction, ft_vec3f_prod(\
		ft_vec3f_diff(h->point, sp->center), sp->radius.reciprocal));
	h->color = sp->color;
}
