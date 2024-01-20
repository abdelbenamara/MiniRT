/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 17:13:21 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_light_add(t_scene *scene, char **info)
{
	t_light	*light;
	t_list	*new;
	t_vec3	*u;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	light = malloc(sizeof(t_light));
	new = ft_lstnew(light);
	if (!light || !new)
		return (ft_pstderr(__ERR_2), free(light), free(new), 0);
	u = ft_vec3_init(info[1]);
	if (!u)
		return (ft_lstdelone(new, free), 0);
	light->position = *u;
	free(u);
	light->bratio = ft_atof(info[2]);
	if (isnan(light->bratio))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), 0);
	if (light->bratio < 0.0 || light->bratio > 1.0)
		return (ft_pstderr(__ERR_6), ft_lstdelone(new, free), 0);
	light->color = ft_color_init(info[3]);
	if (light->color == -1)
		return (ft_lstdelone(new, free), 0);
	ft_lstadd_front(&scene->lights, new);
	return (1);
}
