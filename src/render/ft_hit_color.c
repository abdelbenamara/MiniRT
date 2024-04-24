/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:04:17 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 04:15:10 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool
	ft_scene_hit(t_scene const *const scene, \
		t_point3f const origin, t_vec3f const direction, t_hit *const h)
{
	t_ray	r;
	t_list	*lst;

	r.origin = origin;
	r.direction = direction;
	h->t = INFINITY;
	lst = scene->spheres;
	while (lst)
		(ft_sphere_hit(lst->content, &r, h), lst = lst->next);
	lst = scene->planes;
	while (lst)
		(ft_plane_hit(lst->content, &r, h), lst = lst->next);
	lst = scene->cylinders;
	while (lst)
		(ft_cylinder_hit(lst->content, &r, h), lst = lst->next);
	if (!isfinite(h->t))
		return (false);
	return (true);
}

static t_color3f	ft_color3f_prod(t_color3f const c1, t_color3f const c2)
{
	return (ft_vec3f(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z));
}

static bool
	ft_light_color(t_scene const *const scene, \
		t_hit const *const h, t_vec3f *const nextdir, t_color3f *const diffuse)
{
	t_vec3f		dir;
	float		dot;
	float		cos;
	t_hit		hit;

	dir = ft_vec3f_diff(scene->light->position, h->point);
	dot = ft_vec3f_dot(dir, dir);
	dir = ft_vec3f_unit(dir);
	cos = ft_vec3f_dot(dir, h->normal);
	if (signbit(cos)
		|| (ft_scene_hit(scene, h->point, dir, &hit) && hit.t * hit.t < dot))
		return (false);
	if (ft_random_float(0.0F, 1.0F) < 0.5F)
		*nextdir = dir;
	*diffuse = ft_vec3f_prod(h->color, cos * scene->light->brightness / dot);
	return (true);
}

t_color3f
	ft_hit_color(t_scene const *const scene, \
		t_point3f const origin, t_vec3f const direction, int const depth)
{
	t_hit		h;
	t_vec3f		nextdir;
	t_color3f	ambient;
	t_color3f	diffuse;

	if (!depth || !ft_scene_hit(scene, origin, direction, &h))
		return (ft_vec3f(0.0F, 0.0F, 0.0F));
	nextdir = ft_vec3f_unit(\
		ft_vec3f(ft_random_float(-1.0F, 1.0F), \
		ft_random_float(-1.0F, 1.0F), ft_random_float(-1.0F, 1.0F)));
	if (signbit(ft_vec3f_dot(nextdir, h.normal)))
		nextdir = ft_vec3f_prod(nextdir, -1.0F);
	ambient = ft_color3f_prod(*scene->ambiance, h.color);
	if (!ft_light_color(scene, &h, &nextdir, &diffuse))
		return (ambient);
	(void) depth;
	return (ft_vec3f_sum(ambient, diffuse));
}
