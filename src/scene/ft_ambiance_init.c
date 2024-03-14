/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiance_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:20:15 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_ambiance_init(t_scene *scene, char **info)
{
	if (scene->ambiance)
		return (ft_pstderr(__ERR_3), 0);
	if (ft_tab_size(info) != 3)
		return (ft_pstderr(__ERR_4), 0);
	scene->ambiance = malloc(sizeof(t_ambiance));
	if (!scene->ambiance)
		return (ft_pstderr(__ERR_2), 0);
	scene->ambiance->lighting = ft_atof(info[1]);
	if (isnanf(scene->ambiance->lighting))
		return (ft_pstderr(__ERR_5), 0);
	if (scene->ambiance->lighting < 0.0F || scene->ambiance->lighting > 1.0F)
		return (ft_pstderr(__ERR_6), 0);
	scene->ambiance->color = ft_color_read(info[2]);
	if (isnanf(scene->ambiance->color.x))
		return (0);
	return (1);
}
