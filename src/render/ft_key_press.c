/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/23 19:05:20 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_focus_next(t_scene *const scene)
{
	if (!scene->focus.next)
		scene->focus.type = (scene->focus.type + 1) % 5;
	if (scene->focus.type == 0)
		return (ft_focus_camera(scene));
	if (scene->focus.type == 1)
		return (ft_focus_light(scene));
	if (!scene->focus.next && scene->focus.type == 2)
		scene->focus.next = scene->spheres;
	else if (!scene->focus.next && scene->focus.type == 3)
		scene->focus.next = scene->planes;
	else if (!scene->focus.next && scene->focus.type == 4)
		scene->focus.next = scene->cylinders;
	if (!scene->focus.next)
		return (ft_focus_next(scene));
	if (scene->focus.type == 2)
		ft_focus_sphere(scene);
	else if (scene->focus.type == 3)
		ft_focus_plane(scene);
	else if (scene->focus.type == 4)
		ft_focus_cylinder(scene);
	scene->focus.next = scene->focus.next->next;
}

static bool	ft_key_resize(int const keycode, t_scene *const scene)
{
	static float const	aglmin = FLT_EPSILON + __M_PIF / 180.0F;
	static float const	aglmax = __M_PIF - FLT_EPSILON - __M_PIF / 180.0F;
	static float const	agl = __M_PIF / 180.0F;
	static float const	fltmin = FLT_EPSILON + 0.1F;
	static float const	fltmax = FLT_MAX - FLT_EPSILON - 0.1F;

	if (keycode == XK_i && scene->focus.vup && scene->camera->fov > aglmin)
		scene->camera->fov -= agl;
	else if (keycode == XK_o && scene->focus.vup && scene->camera->fov < aglmax)
		scene->camera->fov += agl;
	else if (keycode == XK_i && scene->focus.radius
		&& scene->focus.radius->twice > fltmin)
		*scene->focus.radius = ft_radius(scene->focus.radius->twice - 0.1F);
	else if (keycode == XK_o && scene->focus.radius
		&& scene->focus.radius->twice < fltmax)
		*scene->focus.radius = ft_radius(scene->focus.radius->twice + 0.1F);
	else if (keycode == XK_k && scene->focus.arrow
		&& scene->focus.arrow->height > fltmin)
		scene->focus.arrow->height -= 0.1F;
	else if (keycode == XK_l && scene->focus.arrow
		&& scene->focus.arrow->height < fltmax)
		scene->focus.arrow->height += 0.1F;
	else
		return (false);
	return (true);
}

static bool	ft_key_translate(int const keycode, t_scene *const scene)
{
	t_vec3f const	onb[] = {
		ft_vec3f_cross(scene->camera->vup, scene->camera->orientation),
		scene->camera->vup,
		scene->camera->orientation
	};
	t_vec3f			axis;

	if (keycode == XK_w)
		axis = ft_vec3f_prod(onb[2], -0.1F);
	else if (keycode == XK_s)
		axis = ft_vec3f_prod(onb[2], 0.1F);
	else if (keycode == XK_a)
		axis = ft_vec3f_prod(onb[0], -0.1F);
	else if (keycode == XK_d)
		axis = ft_vec3f_prod(onb[0], 0.1F);
	else if (keycode == XK_q)
		axis = ft_vec3f_prod(onb[1], -0.1F);
	else if (keycode == XK_e)
		axis = ft_vec3f_prod(onb[1], 0.1F);
	else
		return (false);
	*scene->focus.position = ft_vec3f_sum(*scene->focus.position, axis);
	return (true);
}

int	ft_key_press(int const keycode, t_xclient *const xclient)
{
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	else if (keycode == XK_Tab)
		ft_focus_next(xclient->scene);
	else if (keycode == XK_c)
		ft_focus_camera(xclient->scene);
	else if (ft_key_resize(keycode, xclient->scene)
		|| ft_key_translate(keycode, xclient->scene)
		|| ft_key_rotate(keycode, xclient->scene))
	{
		if (xclient->scene->focus.arrow && keycode != XK_i && keycode != XK_o)
			*xclient->scene->focus.arrow = ft_arrow(\
				*xclient->scene->focus.position, \
				*xclient->scene->focus.orientation, \
				xclient->scene->focus.arrow->height);
		xclient->update = true;
	}
	return (EXIT_SUCCESS);
}
