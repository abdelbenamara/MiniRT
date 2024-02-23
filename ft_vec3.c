/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:31:39 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/08 23:42:19 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ft_vec3(double x, double y, double z)
{
	t_vec3	u;

	u.x = x;
	u.y = y;
	u.z = z;
	return (u);
}
