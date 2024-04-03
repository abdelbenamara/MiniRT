/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiance_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 00:41:28 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_ambiance_init(t_scene *const scene, char *const *info)
{
	if (scene->ambiance)
		return (ft_pstderr(__ERR_3), false);
	if (ft_tab_size(info) != 3)
		return (ft_pstderr(__ERR_4), false);
	scene->ambiance = malloc(sizeof(t_ambiance));
	if (!scene->ambiance)
		return (ft_pstderr(__ERR_2), false);
	scene->ambiance->lighting = ft_str_to_float(info[1]);
	if (!isfinite(scene->ambiance->lighting))
		return (ft_pstderr(__ERR_5), false);
	if (signbit(scene->ambiance->lighting) || scene->ambiance->lighting > 1.0F)
		return (ft_pstderr(__ERR_6), false);
	scene->ambiance->color = ft_str_to_color3f(info[2]);
	if (isnan(scene->ambiance->color.x))
		return (false);
	return (true);
}
