/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat4f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:03:18 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/30 18:38:29 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_quat4f	ft_quat4f(t_vec3f const xyz, float const w)
{
	t_quat4f	q;

	q.xyz = xyz;
	q.w = w;
	return (q);
}
