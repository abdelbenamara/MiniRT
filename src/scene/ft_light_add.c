/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:21 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 00:27:55 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_light_add(t_scene *const scene, char *const *info)
{
	t_light	*light;
	t_list	*new;

	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), false);
	light = malloc(sizeof(t_light));
	new = ft_lstnew(light);
	if (!light || !new)
		return (ft_pstderr(__ERR_2), free(light), free(new), false);
	light->position = ft_str_to_vec3f(info[1]);
	if (isnan(light->position.x))
		return (ft_lstdelone(new, free), false);
	light->brightness = ft_str_to_float(info[2]);
	if (!isfinite(light->brightness))
		return (ft_pstderr(__ERR_5), ft_lstdelone(new, free), false);
	if (signbit(light->brightness) || light->brightness > 1.0F)
		return (ft_pstderr(__ERR_6), ft_lstdelone(new, free), false);
	light->color = ft_str_to_color3f(info[3]);
	if (isnan(light->color.x))
		return (ft_lstdelone(new, free), false);
	ft_lstadd_front(&scene->lights, new);
	return (true);
}
