/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:20 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/01 01:03:34 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float
	ft_cylinder_hit_t(t_cylinder *const cy, t_ray const r, t_vec3f const ob)
{
	float const		k[2] = {
		ft_vec3f_dot(r.direction, cy->axis), ft_vec3f_dot(ob, cy->axis)
	};
	float const		nb = ft_vec3f_dot(ob, r.direction) - k[0] * k[1];
	float const		c = ft_vec3f_dot(ob, ob) - k[1] * k[1] - cy->radius_squared;
	float			a;
	float			d;

	if (!isfinite(nb) || !isfinite(c) || (signbit(nb) && c >= 0.0F))
		return (NAN);
	a = 1.0F - k[0] * k[0];
	if (a <= FLT_EPSILON)
		return (NAN);
	d = nb * nb - a * c;
	if (!isfinite(d) || signbit(d))
		return (NAN);
	if (c >= 0.0F)
		return ((nb - sqrtf(d)) / a);
	else
		return ((nb + sqrtf(d)) / a);
}

static float
	ft_caps_hit_t(t_cylinder *const cy, \
		t_point3f const origin, float const da, t_vec3f *const center)
{
	float const	tt = ft_vec3f_dot(\
		ft_vec3f_diff(cy->top, origin), cy->axis) / da;
	float const	bt = ft_vec3f_dot(\
		ft_vec3f_diff(cy->base, origin), cy->axis) / da;
	float		t;

	if (!isfinite(tt) || signbit(tt))
		t = bt;
	else if (!isfinite(bt) || signbit(bt))
		t = tt;
	else
		t = fminf(tt, bt);
	if (t == tt)
		*center = cy->top;
	else
		*center = cy->base;
	return (t);
}

static void	ft_caps_hit(t_cylinder *const cy, t_ray const r, t_hit *const h)
{
	float const	da = ft_vec3f_dot(r.direction, cy->axis);
	float		t;
	t_point3f	center;
	t_point3f	point;
	t_vec3f		cp;

	if (fabsf(da) <= FLT_EPSILON)
		return ;
	t = ft_caps_hit_t(cy, r.origin, da, &center);
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	point = ft_vec3f_sum(r.origin, ft_vec3f_prod(r.direction, t));
	cp = ft_vec3f_diff(point, center);
	if (ft_vec3f_dot(cp, cp) > cy->radius_squared)
		return ;
	h->t = t;
	h->point = point;
	if (da > 0.0F)
		h->normal = ft_vec3f_prod(cy->axis, -1.0F);
	else
		h->normal = cy->axis;
	h->color = cy->color;
}

void	ft_cylinder_hit(t_cylinder *const cy, t_ray const r, t_hit *const h)
{
	float const		t = ft_cylinder_hit_t(\
		cy, r, ft_vec3f_diff(cy->base, r.origin));
	t_point3f		point;
	float			d;

	ft_caps_hit(cy, r, h);
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	point = ft_vec3f_sum(r.origin, ft_vec3f_prod(r.direction, t));
	d = ft_vec3f_dot(ft_vec3f_diff(cy->top, point), cy->axis);
	if (signbit(d) || d > cy->height)
		return ;
	h->t = t;
	h->point = point;
	h->normal = ft_face_normal(r.direction, ft_vec3f_prod(\
		ft_vec3f_diff(h->point, ft_vec3f_sum(cy->base, \
		ft_vec3f_prod(cy->axis, d))), cy->radius_reciprocal));
	h->color = cy->color;
}
