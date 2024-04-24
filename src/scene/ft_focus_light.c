/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_focus_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:19:58 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/23 19:03:53 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_focus_light(t_scene *const scene)
{
	scene->focus.position = &scene->light->position;
	scene->focus.rotation = NULL;
	scene->focus.orientation = NULL;
	scene->focus.vup = NULL;
	scene->focus.radius = NULL;
	scene->focus.arrow = NULL;
	printf("Info: keys mapped for L\n");
}
