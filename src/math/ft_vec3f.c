/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:31:39 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 14:18:15 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_vec3f(float const x, float const y, float const z)
{
	t_vec3f	u;

	u.x = x;
	u.y = y;
	u.z = z;
	return (u);
}
