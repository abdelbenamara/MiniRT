/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:23:38 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/26 13:59:25 by abenamar         ###   ########.fr       */
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

static bool
	ft_scene_hit(t_scene const *const scene, \
		t_point3f const origin, t_vec3f const direction, t_hit *const h)
{
	t_ray	r;
	t_list	*lst;

	r.origin = origin;
	r.direction = direction;
	h->t = INFINITY;
	h->bias = _SHADOW_BIAS;
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

static t_color3f
	ft_hit_color(t_scene const *const scene, \
		t_point3f const origin, t_vec3f const direction)
{
	t_hit		h[2];
	t_vec3f		lightdir;
	float		ld2cosr[3];
	t_color3f	ambient;

	if (!ft_scene_hit(scene, origin, direction, h))
		return (ft_vec3f(0.0F, 0.0F, 0.0F));
	lightdir = ft_vec3f_diff(scene->light->position, h->point);
	ld2cosr[0] = ft_vec3f_dot(lightdir, lightdir);
	lightdir = ft_vec3f_unit(lightdir);
	ld2cosr[1] = ft_vec3f_dot(lightdir, h->normal);
	ambient = ft_vec3f(scene->ambiance->x * h->color.x, \
		scene->ambiance->y * h->color.y, scene->ambiance->z * h->color.z);
	if (signbit(ld2cosr[1]) || (ft_scene_hit(scene, h->point, lightdir, h + 1)
			&& h[1].t * h[1].t < ld2cosr[0]))
		return (ambient);
	ld2cosr[2] = ld2cosr[1] * scene->light->brightness;
	return (ft_vec3f_sum(ambient, \
		ft_vec3f_prod(h->color, fmaxf(ld2cosr[2], ld2cosr[2] / ld2cosr[0]))));
}

static float	ft_random_float(float const min, float const max)
{
	static float const	rand_max_reciprocal = 1.0F / ((float) RAND_MAX + 1.0F);

	return (min + (max - min) * rand() * rand_max_reciprocal);
}

t_color3f	ft_ray_tracing(t_scene const *const scene, int const i, int const j)
{
	t_viewport const	vp = ft_viewport(scene->camera);
	t_point3f const		target = ft_vec3f_sum(vp.p00, \
		ft_vec3f_sum(ft_vec3f_prod(vp.pdu, i), ft_vec3f_prod(vp.pdv, j)));
	t_vec3f const		origin = scene->camera->position;
	int					k;
	t_color3f			color;

	color = ft_hit_color(scene, origin, \
		ft_vec3f_unit(ft_vec3f_diff(target, origin)));
	k = 1;
	while (k < _SAMPLES_PER_PIXEL)
	{
		color = ft_vec3f_sum(color, ft_hit_color(scene, origin, \
			ft_vec3f_unit(ft_vec3f_diff(ft_vec3f_sum(target, \
			ft_vec3f_sum(ft_vec3f_prod(vp.pdu, ft_random_float(-0.5F, 0.5F)), \
			ft_vec3f_prod(vp.pdv, ft_random_float(-0.5F, 0.5F)))), origin))));
		++k;
	}
	return (color);
}
