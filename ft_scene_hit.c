/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:48:52 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/22 23:06:42 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_sphere_hit(t_sphere *s, t_ray r, t_interval i, t_hit *h)
{
	const t_vec3	oc = ft_vec3_diff(r.origin, s->center);
	const t_vec3	abc = ft_vec3(ft_vec3_length_squared(r.direction), \
		ft_vec3_dot(oc, r.direction), \
			ft_vec3_length_squared(oc) - pow(s->diameter / 2.0, 2.0));
	const double	d = pow(abc.y, 2.0) - abc.x * abc.z;
	double			sqrt_d;
	double			root;

	if (d < 0)
		return (0);
	sqrt_d = sqrt(d);
	root = (-abc.y - sqrt_d) / abc.x;
	if (root <= i.min || root >= i.max)
	{
		root = (-abc.y + sqrt_d) / abc.x;
		if (root <= i.min || root >= i.max)
			return (0);
	}
	h->t = root;
	h->point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, h->t));
	h->color = s->color;
	return (1);
}

t_color	ft_scene_hit(t_scene *scene, t_ray r, t_interval i)
{
	t_hit	h;
	t_list	*lst;

	h.t = i.max;
	h.point = ft_vec3(nan(""), nan(""), nan(""));
	h.color = ft_vec3(0.0, 0.0, 0.0);
	lst = scene->spheres;
	while (lst)
	{
		if (ft_sphere_hit(lst->content, r, i, &h))
			i.max = h.t;
		lst = lst->next;
	}
	return (h.color);
}
