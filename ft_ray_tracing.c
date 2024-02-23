/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:23:38 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/23 20:52:10 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_color_sample(t_scene *scene, t_viewport vp, t_point3 p)
{
	const t_point3	cp = scene->camera->position;
	int				k;
	t_color			color;

	k = 0;
	color = ft_scene_hit(scene, ft_ray(cp, ft_vec3_diff(p, cp)), \
		ft_interval(0.001, INFINITY));
	while (k < _SPP)
	{
		color = ft_vec3_sum(color, ft_scene_hit(scene, ft_ray(cp, \
			ft_vec3_diff(ft_vec3_sum(p, ft_vec3_sum(\
				ft_vec3_prod(vp.pdu, -0.5 * rand() / (RAND_MAX + 1.0)), \
					ft_vec3_prod(vp.pdv, -0.5 * rand() / (RAND_MAX + 1.0)))), \
						cp)), ft_interval(0.001, INFINITY)));
		++k;
	}
	return (ft_color_build(color, _SPP + 1));
}

void	ft_ray_tracing(t_xclient *xclient)
{
	const t_viewport	vp = ft_viewport(xclient->scene->camera);
	int					i;
	int					j;

	ft_xclient_buffer(xclient);
	j = 0;
	while (j < _HEIGHT)
	{
		i = 0;
		while (i < _WIDTH)
		{
			ft_pixel_put(xclient, i, j, \
				ft_color_sample(xclient->scene, vp, \
					ft_vec3_sum(vp.p00, ft_vec3_sum(\
						ft_vec3_prod(vp.pdu, i), ft_vec3_prod(vp.pdv, j)))));
			++i;
		}
		++j;
	}
	ft_xclient_flush(xclient);
}
