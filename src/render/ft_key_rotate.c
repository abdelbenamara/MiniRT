/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:30:52 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/20 18:49:30 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_isrotated(int const keycode, t_quat4f *qrot)
{
	static float const	hagl = __M_PIF / 360.0F;
	static float const	nhagl = __M_PIF / -360.0F;
	t_vec3f const		standard[] = {
		ft_vec3f(1.0F, 0.0F, 0.0F),
		ft_vec3f(0.0F, 1.0F, 0.0F),
		ft_vec3f(0.0F, 0.0F, 1.0F)
	};

	if (keycode == XK_Down)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[0], sinf(nhagl)), cosf(nhagl));
	else if (keycode == XK_Up)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[0], sinf(hagl)), cosf(hagl));
	else if (keycode == XK_Right)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[1], sinf(nhagl)), cosf(nhagl));
	else if (keycode == XK_Left)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[1], sinf(hagl)), cosf(hagl));
	else if (keycode == XK_comma)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[2], sinf(nhagl)), cosf(nhagl));
	else if (keycode == XK_period)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[2], sinf(hagl)), cosf(hagl));
	else
		return (false);
	return (true);
}

bool	ft_key_rotate(int const keycode, t_scene *const scene)
{
	t_quat4f	qrot;

	if (!scene->focus.rotation)
		return (false);
	if (!ft_isrotated(keycode, &qrot))
		return (false);
	*scene->focus.rotation = ft_quat4f_unit(\
		ft_quat4f_prod(*scene->focus.rotation, qrot));
	*scene->focus.orientation = ft_vec3f_unit(ft_vec3f_rotate(\
			ft_vec3f(0.0F, 0.0F, 1.0F), *scene->focus.rotation));
	if (scene->focus.vup)
		*scene->focus.vup = ft_vec3f_unit(ft_vec3f_rotate(\
			ft_vec3f(0.0F, 1.0F, 0.0F), *scene->focus.rotation));
	return (true);
}
