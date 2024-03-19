/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:23:38 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/19 00:51:48 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	ft_hit_color(t_scene *scene, t_ray r)
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

static t_color	ft_super_sampling(t_scene *scene, t_viewport vp, t_point3 p)
{
	const t_point3		cp = scene->camera->position;
	int					k;
	t_color				color;

	color = ft_hit_color(scene, ft_ray(cp, ft_vec3_unit(ft_vec3_diff(p, cp))));
	k = 1;
	while (k < _SAMPLES_PER_PIXEL)
	{
		color = ft_vec3_sum(color, ft_hit_color(scene, \
			ft_ray(cp, ft_vec3_unit(ft_vec3_diff(ft_vec3_sum(p, ft_vec3_sum(\
			ft_vec3_prod(vp.pdu, -0.5F * rand() / (RAND_MAX + 1.0F)), \
			ft_vec3_prod(vp.pdv, -0.5F * rand() / (RAND_MAX + 1.0F)))), cp)))));
		++k;
	}
	return (color);
}

void	ft_ray_tracing(t_xclient *xclient)
{
	const t_viewport	vp = ft_viewport(xclient->scene->camera);
	int					i;
	int					j;

	j = 0;
	while (j < _HEIGHT)
	{
		i = 0;
		while (i < _WIDTH)
		{
			ft_pixel_put(xclient, i, j, ft_super_sampling(xclient->scene, vp, \
				ft_vec3_sum(vp.p00, ft_vec3_sum(\
				ft_vec3_prod(vp.pdu, i), ft_vec3_prod(vp.pdv, j)))));
			++i;
		}
		++j;
	}
}
