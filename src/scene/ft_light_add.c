/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:20:25 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_light_add(t_scene *scene, char **info)
{
	t_light	*light;
	t_list	*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	light = malloc(sizeof(t_light));
	new = ft_lstnew(light);
	if (!light || !new)
		return (ft_pstderr(__ERR_2), free(light), free(new), 0);
	light->position = ft_vec3_read(info[1]);
	if (isnanf(light->position.x))
		return (ft_lstdelone(new, free), 0);
	light->brightness = ft_atof(info[2]);
	if (isnanf(light->brightness))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), 0);
	if (light->brightness < 0.0F || light->brightness > 1.0F)
		return (ft_pstderr(__ERR_6), ft_lstdelone(new, free), 0);
	light->color = ft_color_read(info[3]);
	if (isnanf(light->color.x))
		return (ft_lstdelone(new, free), 0);
	ft_lstadd_front(&scene->lights, new);
	return (1);
}
