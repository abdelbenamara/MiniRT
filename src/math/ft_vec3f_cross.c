/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_cross.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:34:50 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 14:31:48 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_vec3f_cross(t_vec3f const u, t_vec3f const v)
{
	return (ft_vec3f(\
		u.y * v.z - u.z * v.y, \
		u.z * v.x - u.x * v.z, \
		u.x * v.y - u.y * v.x));
}
