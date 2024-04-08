/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_focus_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:29:18 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/08 14:27:39 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_focus_plane(t_scene *const scene)
{
	t_plane *const	pl = (t_plane *) scene->focus.next->content;

	scene->focus.position = &pl->point;
	scene->focus.rotation = &pl->rotation;
	scene->focus.orientation = &pl->normal;
	scene->focus.vup = NULL;
	scene->focus.radius = NULL;
	scene->focus.arrow = NULL;
	printf("Info: keys mapped for pl\n");
}
