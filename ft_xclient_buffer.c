/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 09:20:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/08 00:15:41 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_xclient_buffer(t_xclient *xclient)
{
	xclient->mlx = xclient->mlx;
	xclient->buf = mlx_new_image(xclient->mlx, _WIDTH, _HEIGHT);
	if (!xclient->buf)
		(ft_xclient_free(xclient), exit(EXIT_FAILURE));
	xclient->data = mlx_get_data_addr(\
		xclient->buf, &xclient->bpp, &xclient->lsize, &xclient->endian);
}
