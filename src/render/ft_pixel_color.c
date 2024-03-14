/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:05:15 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 15:14:44 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	ft_clamp(float d, float min, float max)
{
	if (d < min)
		return (min);
	if (d > max)
		return (max);
	return (d);
}

int	ft_pixel_color(t_color color, int spp)
{
	const float	scale = 1.0F / spp;
	const int	r = 256 * ft_clamp(sqrtf(color.x * scale), 0.000F, 0.999F);
	const int	g = 256 * ft_clamp(sqrtf(color.y * scale), 0.000F, 0.999F);
	const int	b = 256 * ft_clamp(sqrtf(color.z * scale), 0.000F, 0.999F);

	return (r << 16 | g << 8 | b);
}
