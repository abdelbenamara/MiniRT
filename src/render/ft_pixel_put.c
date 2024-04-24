/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:19:40 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/23 15:33:25 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	ft_gamma_clamp(float const d)
{
	if (isnan(d) || signbit(d) || d < 0.000F)
		return (0.0F);
	if (d > 0.999F)
		return (0.999F);
	return (sqrtf(d));
}

static int	ft_color_rgb(t_color3f const color)
{
	static float const	scale = 1.0F / (float) _SAMPLES_PER_PIXEL;
	int					r;
	int					g;
	int					b;

	r = 256 * ft_gamma_clamp(color.x * scale);
	g = 256 * ft_gamma_clamp(color.y * scale);
	b = 256 * ft_gamma_clamp(color.z * scale);
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
