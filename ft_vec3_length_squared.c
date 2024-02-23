/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_length_squared.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:18:36 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/22 23:10:30 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_vec3_length_squared(t_vec3 u)
{
	return (pow(u.x, 2.0) + pow(u.y, 2.0) + pow(u.z, 2.0));
}
