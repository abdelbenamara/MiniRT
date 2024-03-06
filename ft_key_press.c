/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/05 23:24:55 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_transformation_handle(int keycode, t_point3 *p, t_vec3 *t)
{
	if (keycode == XK_Up)
		return (p->z -= 0.1, 1);
	if (keycode == XK_Down)
		return (p->z += 0.1, 1);
	if (keycode == XK_Left)
		return (p->x -= 0.1, 1);
	if (keycode == XK_Right)
		return (p->x += 0.1, 1);
	if (keycode == XK_z)
		return (p->y -= 0.1, 1);
	if (keycode == XK_space)
		return (p->y += 0.1, 1);
	if (keycode == XK_s)
		return (t->z -= 1.0, 1);
	if (keycode == XK_w)
		return (t->z += 1.0, 1);
	if (keycode == XK_d)
		return (t->y -= 1.0, 1);
	if (keycode == XK_a)
		return (t->y += 1.0, 1);
	if (keycode == XK_e)
		return (t->x -= 1.0, 1);
	if (keycode == XK_r)
		return (t->x += 1.0, 1);
	return (0);
}

static uint8_t	ft_camera_handle(int keycode, t_camera *camera)
{
	if (keycode == XK_i && camera->fov > 0)
		return (--camera->fov, 1);
	if (keycode == XK_o && camera->fov < 179)
		return (++camera->fov, 1);
	return (ft_transformation_handle(keycode, \
		&camera->position, &camera->theta));
}

int	ft_key_press(int keycode, t_xclient *xclient)
{
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	else if (ft_camera_handle(keycode, xclient->scene->camera))
		xclient->update = 1;
	return (EXIT_SUCCESS);
}
