/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:55:03 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/08 23:42:19 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ft_ray(t_point3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}
