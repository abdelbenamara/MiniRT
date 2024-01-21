/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perspective_projection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:51:43 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/22 00:38:21 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	ft_camera_transform(t_vec3 a, t_vec3 c, t_vec3 t)
{
	t_vec3	u;
	t_vec3	d;

	u.x = a.x - c.x;
	u.y = a.y - c.y;
	u.z = a.z - c.z;
	d.x = cos(t.y) * (cos(t.z) * u.x + sin(t.z) * u.y) - sin(t.y) * u.z;
	d.y = cos(t.x) * (cos(t.z) * u.y - sin(t.z) * u.x) + sin(t.x) * \
		(sin(t.y) * (cos(t.z) * u.x + sin(t.z) * u.y) + cos(t.y) * u.z);
	d.z = cos(t.x) * \
		(sin(t.y) * (cos(t.z) * u.x + sin(t.z) * u.y) + cos(t.y) * u.z) - \
		sin(t.x) * (cos(t.z) * u.y - sin(t.z) * u.x);
	return (d);
}

t_vec2	ft_perspective_projection(t_vec3 a, t_vec3 c, t_vec3 t)
{
	const t_vec3	d = ft_camera_transform(a, c, t);
	t_vec2			b;

	b.x = round(d.x);
	b.y = round(d.y);
	return (b);
}
