/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:19:48 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/24 00:11:51 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_viewport	ft_viewport(t_camera *camera)
{
	const t_vec3	co = camera->orientation;
	const double	f_l = ft_vec3_length(co);
	const double	v_w = 2.0 * tan((camera->fov * M_PI / 180.0) / 2.0) * f_l;
	const t_vec3	u = ft_vec3_unit(ft_vec3_cross(ft_vec3(0.0, 1.0, 0.0), co));
	t_viewport		vp;

	vp.u = ft_vec3_prod(u, v_w);
	vp.v = ft_vec3_prod(ft_vec3_cross(co, u), -v_w * (double) _HEIGHT / _WIDTH);
	vp.pdu = ft_vec3_prod(vp.u, 1.0 / _WIDTH);
	vp.pdv = ft_vec3_prod(vp.v, 1.0 / _HEIGHT);
	vp.p00 = ft_vec3_sum(ft_vec3_diff(ft_vec3_diff(\
		ft_vec3_diff(camera->position, ft_vec3_prod(co, f_l)), \
			ft_vec3_prod(vp.u, 0.5)), ft_vec3_prod(vp.v, 0.5)), \
				ft_vec3_prod(ft_vec3_sum(vp.pdu, vp.pdv), 0.5));
	return (vp);
}
