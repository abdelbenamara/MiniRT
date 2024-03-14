/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:19:48 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/13 13:44:27 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_viewport	ft_viewport(t_camera *camera)
{
	const t_vec3	o = ft_vec3_unit(\
		ft_vec3_rotate(camera->orientation, camera->theta));
	const float		v_w = 2.0F * tanf((camera->fov * __M_PIF / 180.0F) * 0.5F);
	const t_vec3	u = ft_vec3_unit(ft_vec3_cross(\
		ft_vec3_rotate(ft_vec3(0.0F, 1.0F, 0.0F), camera->theta), o));
	t_viewport		vp;

	vp.u = ft_vec3_prod(u, v_w);
	vp.v = ft_vec3_prod(ft_vec3_cross(o, u), -v_w * _HEIGHT / _WIDTH);
	vp.pdu = ft_vec3_prod(vp.u, 1.0F / _WIDTH);
	vp.pdv = ft_vec3_prod(vp.v, 1.0F / _HEIGHT);
	vp.p00 = ft_vec3_sum(ft_vec3_diff(ft_vec3_diff(\
		ft_vec3_diff(camera->position, o), \
		ft_vec3_prod(vp.u, 0.5F)), ft_vec3_prod(vp.v, 0.5F)), \
		ft_vec3_prod(ft_vec3_sum(vp.pdu, vp.pdv), 0.5F));
	return (vp);
}
