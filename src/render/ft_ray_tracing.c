/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:23:38 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 02:21:23 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_viewport	ft_viewport(t_camera const *const camera)
{
	float const		vpw = 2.0F * tanf(0.5F * camera->fov);
	t_vec3f const	u = ft_vec3f_cross(camera->vup, camera->orientation);
	t_viewport		viewport;

	viewport.u = ft_vec3f_prod(u, vpw);
	viewport.v = ft_vec3f_prod(\
		ft_vec3f_cross(camera->orientation, u), -vpw * _HEIGHT / _WIDTH);
	viewport.pdu = ft_vec3f_prod(viewport.u, 1.0F / _WIDTH);
	viewport.pdv = ft_vec3f_prod(viewport.v, 1.0F / _HEIGHT);
	viewport.p00 = ft_vec3f_sum(ft_vec3f_diff(ft_vec3f_diff(\
		ft_vec3f_diff(camera->position, camera->orientation), \
		ft_vec3f_prod(viewport.u, 0.5F)), ft_vec3f_prod(viewport.v, 0.5F)), \
		ft_vec3f_prod(ft_vec3f_sum(viewport.pdu, viewport.pdv), 0.5F));
	return (viewport);
}

static t_ray	ft_ray(t_point3f const origin, t_vec3f const direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

static t_color3f	ft_hit_color(t_scene const *const scene, t_ray const r)
{
	t_hit	h;
	t_list	*lst;

	h.t = INFINITY;
	h.color = ft_vec3f(0.0F, 0.0F, 0.0F);
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

t_color3f	ft_ray_tracing(t_scene const *const scene, int const i, int const j)
{
	t_viewport const	vp = ft_viewport(scene->camera);
	t_point3f const		point = ft_vec3f_sum(vp.p00, ft_vec3f_sum(\
		ft_vec3f_prod(vp.pdu, i), ft_vec3f_prod(vp.pdv, j)));
	t_vec3f const		origin = scene->camera->position;
	int					k;
	t_color3f			color;

	color = ft_hit_color(\
		scene, ft_ray(origin, ft_vec3f_unit(ft_vec3f_diff(point, origin))));
	k = 1;
	while (k < _SAMPLES_PER_PIXEL)
	{
		color = ft_vec3f_sum(color, ft_hit_color(scene, \
			ft_ray(origin, ft_vec3f_unit(ft_vec3f_diff(\
			ft_vec3f_sum(point, ft_vec3f_sum(\
			ft_vec3f_prod(vp.pdu, -0.5F * rand() / (RAND_MAX + 1.0F)), \
			ft_vec3f_prod(vp.pdv, -0.5F * rand() / (RAND_MAX + 1.0F)))), \
			origin)))));
		++k;
	}
	return (color);
}
