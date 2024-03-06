/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:19:48 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/05 23:24:08 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	ft_rotate(t_vec3 a, t_vec3 theta)
{
	const t_vec3	t = ft_vec3_prod(theta, M_PI / 180.0);
	const t_vec3	r = ft_vec3(\
		a.x, cos(t.z) * a.y - sin(t.z) * a.z, sin(t.z) * a.y + cos(t.z) * a.z);
	const t_vec3	p = ft_vec3(\
		cos(t.y) * r.x + sin(t.y) * r.z, r.y, cos(t.y) * r.z - sin(t.y) * r.x);
	const t_vec3	y = ft_vec3(\
		cos(t.x) * p.x - sin(t.x) * p.y, sin(t.x) * p.x + cos(t.x) * p.y, p.z);

	return (y);
}

t_viewport	ft_viewport(t_camera *camera)
{
	const t_vec3	o = ft_vec3_unit(\
		ft_rotate(camera->orientation, camera->theta));
	const double	f_l = ft_vec3_length(o);
	const double	v_w = 2.0 * tan((camera->fov * M_PI / 180.0) / 2.0) * f_l;
	const t_vec3	u = ft_vec3_unit(\
		ft_vec3_cross(ft_rotate(ft_vec3(0.0, 1.0, 0.0), camera->theta), o));
	t_viewport		vp;

	vp.u = ft_vec3_prod(u, v_w);
	vp.v = ft_vec3_prod(ft_vec3_cross(o, u), -v_w * (double) _HEIGHT / _WIDTH);
	vp.pdu = ft_vec3_prod(vp.u, 1.0 / _WIDTH);
	vp.pdv = ft_vec3_prod(vp.v, 1.0 / _HEIGHT);
	vp.p00 = ft_vec3_sum(ft_vec3_diff(ft_vec3_diff(\
		ft_vec3_diff(camera->position, ft_vec3_prod(o, f_l)), \
			ft_vec3_prod(vp.u, 0.5)), ft_vec3_prod(vp.v, 0.5)), \
				ft_vec3_prod(ft_vec3_sum(vp.pdu, vp.pdv), 0.5));
	return (vp);
}
