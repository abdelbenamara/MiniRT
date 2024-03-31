/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:19:40 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 14:36:38 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	ft_scale(int const samples_per_pixel)
{
	if (samples_per_pixel > 0)
		return (1.0F / samples_per_pixel);
	return (1.0F);
}

static float	ft_clamp(float const d, float const min, float const max)
{
	if (d < min)
		return (min);
	if (d > max)
		return (max);
	return (d);
}

static int	ft_color_rgb(t_color3f const color)
{
	float const	scale = ft_scale(_SAMPLES_PER_PIXEL);
	int			r;
	int			g;
	int			b;

	r = 256 * ft_clamp(sqrtf(color.x * scale), 0.000F, 0.999F);
	g = 256 * ft_clamp(sqrtf(color.y * scale), 0.000F, 0.999F);
	b = 256 * ft_clamp(sqrtf(color.z * scale), 0.000F, 0.999F);
	return (r << 16 | g << 8 | b);
}

void	ft_pixel_put(t_xclient const *const xclient, \
	int const x, int const y, t_color3f const color)
{
	char	*pos;

	if (x < 0 || x >= _WIDTH || y < 0 || y >= _HEIGHT)
		return ;
	pos = xclient->data + x * (xclient->bpp / 8) + y * xclient->lsize;
	*((unsigned int *) pos) = mlx_get_color_value(\
		xclient->mlx, ft_color_rgb(color));
}
