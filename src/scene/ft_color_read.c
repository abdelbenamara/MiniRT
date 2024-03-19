/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:11:12 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/19 00:37:30 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ft_color_read(const char *str)
{
	char			*comma[2];
	t_color			rgb;

	comma[0] = ft_strchr(str, ',');
	comma[1] = NULL;
	if (comma[0])
		comma[1] = ft_strchr(comma[0] + 1, ',');
	if (!comma[1] || ft_strchr(comma[1] + 1, ','))
		return (ft_pstderr(__ERR_7), ft_vec3(NAN, NAN, NAN));
	rgb.x = ft_atoi(str);
	rgb.y = ft_atoi(comma[0] + 1);
	rgb.z = ft_atoi(comma[1] + 1);
	if (rgb.x < 0.0F || rgb.y < 0.0F || rgb.z < 0.0F
		|| rgb.x > 255.0F || rgb.y > 255.0F || rgb.z > 255.0F)
		return (ft_pstderr(__ERR_8), ft_vec3(NAN, NAN, NAN));
	return (ft_vec3_prod(rgb, 1.0F / 255.0F));
}
