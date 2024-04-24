/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_color3f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:11:12 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 13:45:03 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color3f	ft_str_to_color3f(char const *str)
{
	char			*comma[2];
	t_color3f		rgb;

	comma[0] = ft_strchr(str, ',');
	comma[1] = NULL;
	if (comma[0])
		comma[1] = ft_strchr(comma[0] + 1, ',');
	if (!comma[1] || ft_strchr(comma[1] + 1, ','))
		return (ft_pstderr(__ERR_11), ft_vec3f(NAN, NAN, NAN));
	rgb.x = ft_atoi(str);
	rgb.y = ft_atoi(comma[0] + 1);
	rgb.z = ft_atoi(comma[1] + 1);
	if (signbit(rgb.x) || signbit(rgb.y) || signbit(rgb.z)
		|| rgb.x > 255.0F || rgb.y > 255.0F || rgb.z > 255.0F)
		return (ft_pstderr(__ERR_12), ft_vec3f(NAN, NAN, NAN));
	return (ft_vec3f_prod(rgb, 1.0F / 255.0F));
}
