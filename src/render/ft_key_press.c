/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/13 17:55:02 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_translate(int keycode, t_point3 *point, t_vec3 *theta)
{
	if (keycode == XK_w)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, 0.0F, -0.1F), *theta)), 1);
	if (keycode == XK_s)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, 0.0F, 0.1F), *theta)), 1);
	if (keycode == XK_a)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(-0.1F, 0.0F, 0.0F), *theta)), 1);
	if (keycode == XK_d)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.1F, 0.0F, 0.0F), *theta)), 1);
	if (keycode == XK_q)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, -0.1F, 0.0F), *theta)), 1);
	if (keycode == XK_e)
		return (*point = ft_vec3_sum(*point, \
			ft_vec3_rotate(ft_vec3(0.0F, 0.1F, 0.0F), *theta)), 1);
	return (0);
}

static uint8_t	ft_transform(int keycode, t_point3 *point, t_vec3 *theta)
{
	if (ft_translate(keycode, point, theta))
		return (1);
	if (keycode == XK_Down)
		return (theta->z -= 1.0F, 1);
	if (keycode == XK_Up)
		return (theta->z += 1.0F, 1);
	if (keycode == XK_Right)
		return (theta->y -= 1.0F, 1);
	if (keycode == XK_Left)
		return (theta->y += 1.0F, 1);
	if (keycode == XK_comma)
		return (theta->x -= 1.0F, 1);
	if (keycode == XK_period)
		return (theta->x += 1.0F, 1);
	return (0);
}

static uint8_t	ft_camera_handle(int keycode, t_camera *camera)
{
	if (keycode == XK_i && camera->fov > 0)
		return (--camera->fov, 1);
	if (keycode == XK_o && camera->fov < 179)
		return (++camera->fov, 1);
	return (ft_transform(keycode, &camera->position, &camera->theta));
}

int	ft_key_press(int keycode, t_xclient *xclient)
{
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	else if (ft_camera_handle(keycode, xclient->scene->camera))
		xclient->update = 1;
	return (EXIT_SUCCESS);
}
