/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 13:40:55 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_light_init(t_scene *const scene, char *const *info)
{
	if (scene->light)
		return (ft_pstderr(__ERR_07), false);
	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_08), false);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		return (ft_pstderr(__ERR_06), false);
	scene->light->position = ft_str_to_vec3f(info[1]);
	if (isnan(scene->light->position.x))
		return (false);
	scene->light->brightness = ft_str_to_float(info[2]);
	if (!isfinite(scene->light->brightness))
		return (ft_pstderr(__ERR_09), false);
	if (signbit(scene->light->brightness) || scene->light->brightness > 1.0F)
		return (ft_pstderr(__ERR_10), false);
	scene->light->color = ft_str_to_color3f(info[3]);
	if (isnan(scene->light->color.x))
		return (false);
	return (true);
}
