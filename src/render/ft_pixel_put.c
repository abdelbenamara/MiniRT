/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:19:40 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/26 14:14:31 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	ft_gamma_clamp(float const value)
{
	if (isnan(value) || signbit(value))
		return (0.0F);
	if (value > 0.999F)
		return (0.999F);
	return (sqrtf(value));
}

static int	ft_rgb(t_color3f const *const color)
{
	static float const	scale = 1.0F / (float) _SAMPLES_PER_PIXEL;
	int					r;
	int					g;
	int					b;

	r = 256 * ft_gamma_clamp(color->x * scale);
	g = 256 * ft_gamma_clamp(color->y * scale);
	b = 256 * ft_gamma_clamp(color->z * scale);
	return (r << 16 | g << 8 | b);
}

void
	ft_pixel_put(t_xclient const *const xclient, \
		int const x, int const y, t_color3f const color)
{
	char	*p;

	if (x < 0 || x >= _WIDTH || y < 0 || y >= _HEIGHT)
		return ;
	p = xclient->data + x * (xclient->bpp / 8) + y * xclient->lsize;
	*((unsigned int *) p) = mlx_get_color_value(xclient->mlx, ft_rgb(&color));
}
