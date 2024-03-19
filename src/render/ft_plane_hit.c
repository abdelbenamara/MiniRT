/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:46:45 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/18 14:30:41 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_plane_hit(t_plane *pl, t_ray r, t_hit *h)
{
	const float	dn = ft_vec3_dot(r.direction, pl->normal);
	float		t;

	if (fabsf(dn) <= FLT_EPSILON)
		return ;
	t = ft_vec3_dot(ft_vec3_diff(pl->point, r.origin), pl->normal) / dn;
	if (!isfinite(t) || signbit(t) || h->t <= t)
		return ;
	h->t = t;
	h->point = ft_vec3_sum(r.origin, ft_vec3_prod(r.direction, h->t));
	if (dn > 0.0F)
		h->normal = ft_vec3_prod(pl->normal, -1.0F);
	else
		h->normal = pl->normal;
	h->color = pl->color;
}
