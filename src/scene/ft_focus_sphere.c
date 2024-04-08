/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_focus_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:24:37 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/08 14:27:36 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_focus_sphere(t_scene *const scene)
{
	t_sphere *const	sp = (t_sphere *) scene->focus.next->content;

	scene->focus.position = &sp->center;
	scene->focus.rotation = NULL;
	scene->focus.orientation = NULL;
	scene->focus.vup = NULL;
	scene->focus.radius = &sp->radius;
	scene->focus.arrow = NULL;
	printf("Info: keys mapped for sp\n");
}
