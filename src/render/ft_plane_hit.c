/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:46:45 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/23 20:40:51 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void
	ft_plane_hit(t_plane const *const pl, t_ray const *const r, t_hit *const h)
{
	float const	dn = ft_vec3f_dot(r->direction, pl->normal);
	float		t;

	if (fabsf(dn) <= FLT_EPSILON)
		return ;
	t = ft_vec3f_dot(ft_vec3f_diff(pl->point, r->origin), pl->normal) / dn;
	if (!isfinite(t) || signbit(t) || _SHADOW_BIAS >= t || t >= h->t)
		return ;
	h->t = t;
	h->point = ft_vec3f_sum(r->origin, ft_vec3f_prod(r->direction, h->t));
	if (dn > 0.0F)
		h->normal = ft_vec3f_prod(pl->normal, -1.0F);
	else
		h->normal = pl->normal;
	h->color = pl->color;
}
