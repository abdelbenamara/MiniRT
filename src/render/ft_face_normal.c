/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_face_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:05:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 14:33:12 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_face_normal(t_vec3f const direction, t_vec3f const normal)
{
	if (ft_vec3f_dot(direction, normal) > 0.0F)
		return (ft_vec3f_prod(normal, -1.0F));
	return (normal);
}
