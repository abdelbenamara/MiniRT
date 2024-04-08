/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radius.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:54:49 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/07 20:23:55 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_radius	ft_radius(float const diameter)
{
	t_radius	radius;

	radius.twice = diameter;
	radius.value = diameter * 0.5F;
	radius.square = powf(radius.value, 2.0F);
	radius.reciprocal = powf(radius.value, -1.0F);
	return (radius);
}
