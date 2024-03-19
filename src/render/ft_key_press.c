/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/16 13:28:09 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_translate(int keycode, t_point3 *point, t_vec3 *theta)
{
	if (keycode == XK_w)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, 0.0F, -0.1F), *theta)), true);
	if (keycode == XK_s)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, 0.0F, 0.1F), *theta)), true);
	if (keycode == XK_a)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(-0.1F, 0.0F, 0.0F), *theta)), true);
	if (keycode == XK_d)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.1F, 0.0F, 0.0F), *theta)), true);
	if (keycode == XK_q)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, -0.1F, 0.0F), *theta)), true);
	if (keycode == XK_e)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, 0.1F, 0.0F), *theta)), true);
	return (false);
}

static bool	ft_transform(int keycode, t_point3 *point, t_vec3 *theta)
{
	if (ft_translate(keycode, point, theta))
		return (true);
	if (keycode == XK_Down)
		return (theta->z -= 1.0F, true);
	if (keycode == XK_Up)
		return (theta->z += 1.0F, true);
	if (keycode == XK_Right)
		return (theta->y -= 1.0F, true);
	if (keycode == XK_Left)
		return (theta->y += 1.0F, true);
	if (keycode == XK_comma)
		return (theta->x -= 1.0F, true);
	if (keycode == XK_period)
		return (theta->x += 1.0F, true);
	return (false);
}

static bool	ft_camera_handle(int keycode, t_camera *camera)
{
	if (keycode == XK_i && camera->fov > 0)
		return (--camera->fov, true);
	if (keycode == XK_o && camera->fov < 179)
		return (++camera->fov, true);
	return (ft_transform(keycode, &camera->position, &camera->theta));
}

int	ft_key_press(int keycode, t_xclient *xclient)
{
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	else
		xclient->update = ft_camera_handle(keycode, xclient->scene->camera);
	return (EXIT_SUCCESS);
}
