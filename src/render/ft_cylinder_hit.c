/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:20 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/19 00:37:30 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	ft_cylinder_hit_t(t_cylinder *cy, t_ray r, t_vec3 ob)
{
	const float		k[2] = {
		ft_vec3_dot(r.direction, cy->axis), ft_vec3_dot(ob, cy->axis)
	};
	const float		nb = ft_vec3_dot(ob, r.direction) - k[0] * k[1];
	const float		c = ft_vec3_dot(ob, ob) \
		- powf(k[1], 2.0F) - cy->radius_squared;
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
	ft_caps_hit_t(t_cylinder *cy, t_point3 origin, float da, t_point3 *center)
{
	const float	tt = ft_vec3_dot(ft_vec3_diff(cy->top, origin), cy->axis) / da;
	const float	bt = ft_vec3_dot(ft_vec3_diff(cy->base, origin), cy->axis) / da;
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

static void	ft_caps_hit(t_cylinder *cy, t_ray r, t_hit *h)
{
	const float	da = ft_vec3_dot(r.direction, cy->axis);
	float		t;
	t_point3	center;
	t_point3	point;
	t_vec3		cp;

	if (fabsf(da) <= FLT_EPSILON)
		return ;
	t = ft_caps_hit_t(cy, r.origin, da, &center);
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, t));
	cp = ft_vec3_diff(point, center);
	if (ft_vec3_dot(cp, cp) > cy->radius_squared)
		return ;
	h->t = t;
	h->point = point;
	if (da > 0.0F)
		h->normal = ft_vec3_prod(cy->axis, -1.0F);
	else
		h->normal = cy->axis;
	h->color = cy->color;
}

void	ft_cylinder_hit(t_cylinder *cy, t_ray r, t_hit *h)
{
	const float		t = ft_cylinder_hit_t(\
		cy, r, ft_vec3_diff(cy->base, r.origin));
	t_point3		p;
	float			d;

	ft_caps_hit(cy, r, h);
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	p = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, t));
	d = ft_vec3_dot(ft_vec3_diff(cy->top, p), cy->axis);
	if (signbit(d) || d > cy->height)
		return ;
	h->t = t;
	h->point = p;
	h->normal = ft_face_normal(r.direction, ft_vec3_prod(\
		ft_vec3_diff(h->point, ft_vec3_sum(cy->base, \
		ft_vec3_prod(cy->axis, d))), cy->radius_reciprocal));
	h->color = cy->color;
}
