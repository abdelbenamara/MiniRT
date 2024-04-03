/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 02:04:53 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_basis	ft_basis(t_vec3f const x, t_vec3f const y, t_vec3f const z)
{
	t_basis	basis;

	basis.x = x;
	basis.y = y;
	basis.z = z;
	return (basis);
}

static bool
	ft_key_translate(int const keycode, \
		t_camera *const camera, t_point3f *const position)
{
	t_basis const	orthogonal = ft_basis(\
		ft_vec3f_cross(camera->vup, camera->orientation), \
		camera->vup, camera->orientation);
	t_vec3f			axis;

	if (keycode == XK_w)
		axis = ft_vec3f_prod(orthogonal.z, -0.1F);
	else if (keycode == XK_s)
		axis = ft_vec3f_prod(orthogonal.z, 0.1F);
	else if (keycode == XK_a)
		axis = ft_vec3f_prod(orthogonal.x, -0.1F);
	else if (keycode == XK_d)
		axis = ft_vec3f_prod(orthogonal.x, 0.1F);
	else if (keycode == XK_q)
		axis = ft_vec3f_prod(orthogonal.y, -0.1F);
	else if (keycode == XK_e)
		axis = ft_vec3f_prod(orthogonal.y, 0.1F);
	else
		return (false);
	*position = ft_vec3f_sum(*position, axis);
	return (true);
}

static bool
	ft_key_rotate(int const keycode, t_quat4f *const rotation, \
		t_vec3f *const orientation, t_vec3f *const vup)
{
	static float const	hagl = __M_PIF / 360.0F;
	static float const	nhagl = __M_PIF / -360.0F;
	t_basis const		standard = ft_basis(ft_vec3f(1.0F, 0.0F, 0.0F), \
		ft_vec3f(0.0F, 1.0F, 0.0F), ft_vec3f(0.0F, 0.0F, 1.0F));
	t_quat4f			qrot;

	if (keycode == XK_Down)
		qrot = ft_quat4f(ft_vec3f_prod(standard.x, sinf(nhagl)), cosf(nhagl));
	else if (keycode == XK_Up)
		qrot = ft_quat4f(ft_vec3f_prod(standard.x, sinf(hagl)), cosf(hagl));
	else if (keycode == XK_Right)
		qrot = ft_quat4f(ft_vec3f_prod(standard.y, sinf(nhagl)), cosf(nhagl));
	else if (keycode == XK_Left)
		qrot = ft_quat4f(ft_vec3f_prod(standard.y, sinf(hagl)), cosf(hagl));
	else if (keycode == XK_comma)
		qrot = ft_quat4f(ft_vec3f_prod(standard.z, sinf(nhagl)), cosf(nhagl));
	else if (keycode == XK_period)
		qrot = ft_quat4f(ft_vec3f_prod(standard.z, sinf(hagl)), cosf(hagl));
	else
		return (false);
	*rotation = ft_quat4f_unit(ft_quat4f_prod(*rotation, qrot));
	*orientation = ft_vec3f_unit(ft_vec3f_rotate(standard.z, *rotation));
	if (vup)
		*vup = ft_vec3f_unit(ft_vec3f_rotate(standard.y, *rotation));
	return (true);
}

int	ft_key_press(int const keycode, t_xclient *const xclient)
{
	static float const	min_agl = FLT_EPSILON + __M_PIF / 180.0F;
	static float const	max_agl = __M_PIF - FLT_EPSILON - __M_PIF / 180.0F;
	static float const	agl = __M_PIF / 180.0F;

	xclient->update = true;
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	else if (keycode == XK_i && xclient->scene->camera->fov > min_agl)
		xclient->scene->camera->fov -= agl;
	else if (keycode == XK_o && xclient->scene->camera->fov < max_agl)
		xclient->scene->camera->fov += agl;
	else if (ft_key_translate(keycode, xclient->scene->camera, \
		&xclient->scene->camera->position))
		;
	else if (ft_key_rotate(keycode, &xclient->scene->camera->rotation, \
		&xclient->scene->camera->orientation, &xclient->scene->camera->vup))
		;
	else
		xclient->update = false;
	return (EXIT_SUCCESS);
}
