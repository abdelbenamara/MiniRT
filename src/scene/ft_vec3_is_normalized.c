/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_is_normalized.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:41:11 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/16 13:34:05 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_vec3_is_normalized(t_vec3 u)
{
	if (u.x < -1.0F || u.y < -1.0F || u.z < -1.0F
		|| u.x > 1.0F || u.y > 1.0F || u.z > 1.0F)
		return (ft_pstderr(__ERR_10), false);
	return (true);
}
