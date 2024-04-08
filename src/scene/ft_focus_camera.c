/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_focus_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:11:39 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/08 14:24:25 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_focus_camera(t_scene *const scene)
{
	scene->focus.position = &scene->camera->position;
	scene->focus.rotation = &scene->camera->rotation;
	scene->focus.orientation = &scene->camera->orientation;
	scene->focus.vup = &scene->camera->vup;
	scene->focus.radius = NULL;
	scene->focus.arrow = NULL;
	printf("Info: keys mapped for C\n");
}
