/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_focus_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:31:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/08 14:27:42 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_focus_cylinder(t_scene *const scene)
{
	t_cylinder *const	cy = (t_cylinder *) scene->focus.next->content;

	scene->focus.position = &cy->arrow.center;
	scene->focus.rotation = &cy->rotation;
	scene->focus.orientation = &cy->axis;
	scene->focus.vup = NULL;
	scene->focus.radius = &cy->radius;
	scene->focus.arrow = &cy->arrow;
	printf("Info: keys mapped for cy\n");
}
