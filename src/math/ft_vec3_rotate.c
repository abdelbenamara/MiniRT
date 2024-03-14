/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:06 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/13 13:44:27 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ft_vec3_rotate(t_vec3 u, t_vec3 theta)
{
	const t_vec3	th = ft_vec3_prod(theta, __M_PIF / 180.0F);
	const t_vec3	roll = ft_vec3(\
		u.x, \
		cosf(th.z) * u.y - sinf(th.z) * u.z, \
		sinf(th.z) * u.y + cosf(th.z) * u.z);
	const t_vec3	pitch = ft_vec3(\
		cosf(th.y) * roll.x + sinf(th.y) * roll.z, \
		roll.y, \
		cosf(th.y) * roll.z - sinf(th.y) * roll.x);
	const t_vec3	yaw = ft_vec3(\
		cosf(th.x) * pitch.x - sinf(th.x) * pitch.y, \
		sinf(th.x) * pitch.x + cosf(th.x) * pitch.y, \
		pitch.z);

	return (yaw);
}
