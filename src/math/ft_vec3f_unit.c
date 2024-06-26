/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:33:55 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 16:27:23 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_vec3f_unit(t_vec3f const u)
{
	return (ft_vec3f_prod(u, 1.0F / sqrtf(ft_vec3f_dot(u, u))));
}
