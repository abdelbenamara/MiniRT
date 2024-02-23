/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:05:15 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/09 10:12:35 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	ft_interval_clamp(t_interval i, double d)
{
	if (d < i.min)
		return (i.min);
	if (d > i.max)
		return (i.max);
	return (d);
}

int	ft_color_build(t_color color, int spp)
{
	const t_interval	i = ft_interval(0.000, 0.999);
	const int			r = 256 * ft_interval_clamp(i, sqrt(color.x / spp));
	const int			g = 256 * ft_interval_clamp(i, sqrt(color.y / spp));
	const int			b = 256 * ft_interval_clamp(i, sqrt(color.z / spp));

	return (r << 16 | g << 8 | b);
}
