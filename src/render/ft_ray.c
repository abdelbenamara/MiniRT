/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:55:03 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/01 01:12:57 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ft_ray(t_point3f const origin, t_vec3f const direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}
