/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:41:04 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/23 19:41:59 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_scene_free(t_scene *scene)
{
	free(scene->ambiance);
	free(scene->camera);
	free(scene->light);
	ft_lstclear(&scene->spheres, free);
	ft_lstclear(&scene->planes, free);
	ft_lstclear(&scene->cylinders, free);
	free(scene);
}
