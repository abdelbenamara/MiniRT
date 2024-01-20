/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiance_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:12:11 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 17:13:19 by abenamar         ###   ########.fr       */
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
	scene->ambiance->lratio = ft_atof(info[1]);
	if (isnan(scene->ambiance->lratio))
		return (ft_pstderr(__ERR_5), 0);
	if (scene->ambiance->lratio < 0.0 || scene->ambiance->lratio > 1.0)
		return (ft_pstderr(__ERR_6), 0);
	scene->ambiance->color = ft_color_init(info[2]);
	if (scene->ambiance->color == -1)
		return (0);
	return (1);
}
