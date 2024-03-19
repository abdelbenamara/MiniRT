/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_face_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:05:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/18 14:21:34 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ft_face_normal(t_vec3 direction, t_vec3 normal)
{
	if (ft_vec3_dot(direction, normal) > 0.0F)
		return (ft_vec3_prod(normal, -1.0F));
	return (normal);
}
