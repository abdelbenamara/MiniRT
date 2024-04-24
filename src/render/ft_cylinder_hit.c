/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:20 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 13:50:01 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float
	ft_cylinder_hit_t(t_cylinder const *const cy, \
		t_ray const *const r, t_vec3f const ob)
{
	float const		k[2] = {
		ft_vec3f_dot(r->direction, cy->axis), ft_vec3f_dot(ob, cy->axis)
	};
	float const		nb = ft_vec3f_dot(ob, r->direction) - k[0] * k[1];
	float const		c = ft_vec3f_dot(ob, ob) \
		- powf(k[1], 2.0F) - cy->radius.square;
	float			a;
	float			d;

	if (!isfinite(nb) || !isfinite(c) || (signbit(nb) && c >= 0.0F))
		return (NAN);
	a = 1.0F - powf(k[0], 2.0F);
	if (a <= FLT_EPSILON)
		return (NAN);
	d = powf(nb, 2.0F) - a * c;
	if (!isfinite(d) || signbit(d))
		return (NAN);
	if (c >= 0.0F)
		return ((nb - sqrtf(d)) / a);
	else
		return ((nb + sqrtf(d)) / a);
}

static float
	ft_caps_hit_t(t_cylinder const *const cy, \
		t_ray const *const r, float const da, t_vec3f *const center)
{
	float const	et = ft_vec3f_dot(\
		ft_vec3f_diff(cy->arrow.end, r->origin), cy->axis) / da;
	float const	st = ft_vec3f_dot(\
		ft_vec3f_diff(cy->arrow.start, r->origin), cy->axis) / da;
	float		t;

	if (!isfinite(et) || signbit(et))
		t = st;
	else if (!isfinite(st) || signbit(st))
		t = et;
	else
		t = fminf(et, st);
	if (t == et)
		*center = cy->arrow.end;
	else
		*center = cy->arrow.start;
	return (t);
}

static void
	ft_caps_hit(t_cylinder const *const cy, \
		t_ray const *const r, t_hit *const h)
{
	float const	da = ft_vec3f_dot(r->direction, cy->axis);
	float		t;
	t_point3f	center;
	t_point3f	point;
	t_vec3f		cp;

	if (fabsf(da) <= FLT_EPSILON)
		return ;
	t = ft_caps_hit_t(cy, r, da, &center);
	if (!isfinite(t) || signbit(t) || h->bias >= t || t >= h->t)
		return ;
	point = ft_vec3f_sum(r->origin, ft_vec3f_prod(r->direction, t));
	cp = ft_vec3f_diff(point, center);
	if (ft_vec3f_dot(cp, cp) > cy->radius.square)
		return ;
	h->t = t;
	h->point = point;
	if (da > 0.0F)
		h->normal = ft_vec3f_prod(cy->axis, -1.0F);
	else
		h->normal = cy->axis;
	h->color = cy->color;
}

void
	ft_cylinder_hit(t_cylinder const *const cy, \
		t_ray const *const r, t_hit *const h)
{
	float const		t = ft_cylinder_hit_t(\
		cy, r, ft_vec3f_diff(cy->arrow.start, r->origin));
	t_point3f		point;
	float			d;

	ft_caps_hit(cy, r, h);
	if (!isfinite(t) || signbit(t) || h->bias >= t || t >= h->t)
		return ;
	point = ft_vec3f_sum(r->origin, ft_vec3f_prod(r->direction, t));
	d = ft_vec3f_dot(ft_vec3f_diff(point, cy->arrow.start), cy->axis);
	if (signbit(d) || d > cy->arrow.height)
		return ;
	h->t = t;
	h->point = point;
	h->normal = ft_face_normal(r->direction, ft_vec3f_prod(\
		ft_vec3f_diff(h->point, ft_vec3f_sum(cy->arrow.start, \
		ft_vec3f_prod(cy->axis, d))), cy->radius.reciprocal));
	h->color = cy->color;
}
