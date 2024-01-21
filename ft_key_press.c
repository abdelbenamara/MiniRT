/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:31:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/21 19:35:40 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_key_press(int keycode, t_xclient *xclient)
{
	if (keycode == XK_Escape)
		mlx_loop_end(xclient->mlx);
	return (EXIT_SUCCESS);
}
