/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_isnormalized.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:41:11 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/02 23:53:51 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_vec3f_isnormalized(t_vec3f const u)
{
	if (u.x < -1.0F || u.y < -1.0F || u.z < -1.0F
		|| u.x > 1.0F || u.y > 1.0F || u.z > 1.0F)
		return (ft_pstderr(__ERR_10), false);
	if (fpclassify(u.x) == FP_ZERO
		&& fpclassify(u.y) == FP_ZERO
		&& fpclassify(u.z) == FP_ZERO)
		return (ft_pstderr(__ERR_11), false);
	return (true);
}
