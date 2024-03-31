/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat4f_prod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:11:37 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/31 20:24:59 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_quat4f	ft_quat4f_prod(t_quat4f const q, t_quat4f const p)
{
	return (ft_quat4f(\
		ft_vec3f_sum(ft_vec3f_prod(p.xyz, q.w), \
		ft_vec3f_sum(ft_vec3f_prod(q.xyz, p.w), \
		ft_vec3f_cross(q.xyz, p.xyz))), \
		q.w * p.w - ft_vec3f_dot(q.xyz, p.xyz)));
}
