/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:16:09 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/01 01:14:33 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_vec3f_rotate(t_vec3f const point, t_quat4f const q)
{
	return (ft_quat4f_prod(ft_quat4f_prod(q, ft_quat4f(point, 0.0F)), \
		ft_quat4f(ft_vec3f_prod(q.xyz, -1.0F), q.w)).xyz);
}
