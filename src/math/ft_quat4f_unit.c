/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat4f_unit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:15:40 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/04 20:47:09 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_quat4f	ft_quat4f_unit(t_quat4f const q)
{
	float const	t = 1.0F / sqrtf(powf(q.w, 2.0F) + ft_vec3f_dot(q.xyz, q.xyz));

	return (ft_quat4f(ft_vec3f_prod(q.xyz, t), q.w * t));
}
