/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 14:54:38 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_view_angle_set(t_xclient *xclient, double x, double y, double z)
{
	xclient->xsettings.theta.x = x;
	xclient->xsettings.theta.y = y;
	xclient->xsettings.theta.z = z;
}

static void	ft_rotation_handle(int keycode, t_xclient *xclient)
{
	if (keycode == XK_w)
		++(xclient->xsettings.theta.x);
	else if (keycode == XK_s)
		--(xclient->xsettings.theta.x);
	else if (keycode == XK_a)
		++(xclient->xsettings.theta.z);
	else if (keycode == XK_d)
		--(xclient->xsettings.theta.z);
	else if (keycode == XK_e)
		++(xclient->xsettings.theta.y);
	else if (keycode == XK_q)
		--(xclient->xsettings.theta.y);
	else if (keycode == XK_0)
		ft_view_angle_set(xclient, 0.0, 0.0, 0.0);
}

int	ft_key_press_handle(int keycode, t_xclient *xclient)
{
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	else if (keycode == XK_r)
		ft_xsettings_reset(&(xclient->xsettings));
	else if (keycode == XK_Up)
		xclient->xsettings.origin.y -= HEIGHT / 64;
	else if (keycode == XK_Down)
		xclient->xsettings.origin.y += HEIGHT / 64;
	else if (keycode == XK_Left)
		xclient->xsettings.origin.x -= WIDTH / 64;
	else if (keycode == XK_Right)
		xclient->xsettings.origin.x += WIDTH / 64;
	else
		ft_rotation_handle(keycode, xclient);
	return (EXIT_SUCCESS);
}
