/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/16 13:31:35 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_light_add(t_scene *scene, char **info)
{
	t_light	*light;
	t_list	*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), false);
	light = malloc(sizeof(t_light));
	new = ft_lstnew(light);
	if (!light || !new)
		return (ft_pstderr(__ERR_2), free(light), free(new), false);
	light->position = ft_vec3_read(info[1]);
	if (isnan(light->position.x))
		return (ft_lstdelone(new, free), false);
	light->brightness = ft_atof(info[2]);
	if (isnan(light->brightness))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), false);
	if (light->brightness < 0.0F || light->brightness > 1.0F)
		return (ft_pstderr(__ERR_6), ft_lstdelone(new, free), false);
	light->color = ft_color_read(info[3]);
	if (isnan(light->color.x))
		return (ft_lstdelone(new, free), false);
	ft_lstadd_front(&scene->lights, new);
	return (true);
}
