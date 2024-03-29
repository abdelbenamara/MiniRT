/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_diff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:33:03 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/08 23:42:19 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ft_vec3_diff(t_vec3 u, t_vec3 v)
{
	return (ft_vec3(u.x - v.x, u.y - v.y, u.z - v.z));
}
