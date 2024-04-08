/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:57:53 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/07 20:24:03 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_arrow	ft_arrow(t_point3f const center, t_vec3f const axis, float const height)
{
	t_arrow	arrow;

	arrow.center = center;
	arrow.start = ft_vec3f_diff(\
		arrow.center, ft_vec3f_prod(axis, height * 0.5F));
	arrow.end = ft_vec3f_sum(arrow.start, ft_vec3f_prod(axis, height));
	arrow.height = height;
	return (arrow);
}
