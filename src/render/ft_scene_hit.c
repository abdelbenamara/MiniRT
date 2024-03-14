/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:48:52 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:56:36 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_sphere_hit(t_sphere *sp, t_ray r, t_hit *h)
{
	const t_vec3	oc = ft_vec3_diff(sp->center, r.origin);
	const float		nb = ft_vec3_dot(oc, r.direction);
	const float		c = ft_vec3_dot(oc, oc) - powf(sp->radius, 2.0F);
	float			d;
	float			t;

	if (c >= 0.0F && nb < 0.0F)
		return ;
	d = powf(nb, 2.0F) - c;
	if (d < 0.0F)
		return ;
	if (c >= 0.0F)
		t = nb - sqrtf(d);
	else
		t = nb + sqrtf(d);
	if (t <= FLT_EPSILON || h->t <= t)
		return ;
	h->t = t;
	h->point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, h->t));
	h->normal = ft_vec3_prod(\
		ft_vec3_diff(h->point, sp->center), 1.0F / sp->radius);
	if (ft_vec3_dot(r.direction, h->normal) > 0.0F)
		h->normal = ft_vec3_prod(h->normal, -1.0F);
	h->color = sp->color;
}

static void	ft_plane_hit(t_plane *pl, t_ray r, t_hit *h)
{
	const float	denom = ft_vec3_dot(r.direction, pl->normal);
	float		t;

	if (fabsf(denom) < FLT_EPSILON)
		return ;
	t = ft_vec3_dot(ft_vec3_diff(pl->point, r.origin), pl->normal) / denom;
	if (t < FLT_EPSILON || h->t < t)
		return ;
	h->t = t;
	h->point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, h->t));
	h->normal = pl->normal;
	if (denom > 0.0F)
		h->normal = ft_vec3_prod(h->normal, -1.0F);
	h->color = pl->color;
}

t_color	ft_scene_hit(t_scene *scene, t_ray r)
{
	t_hit	h;
	t_list	*lst;

	h.t = INFINITY;
	h.color = ft_vec3(0.0F, 0.0F, 0.0F);
	lst = scene->spheres;
	while (lst)
		(ft_sphere_hit(lst->content, r, &h), lst = lst->next);
	lst = scene->planes;
	while (lst)
		(ft_plane_hit(lst->content, r, &h), lst = lst->next);
	lst = scene->cylinders;
	while (lst)
		(ft_cylinder_hit(lst->content, r, &h), lst = lst->next);
	return (h.color);
}
