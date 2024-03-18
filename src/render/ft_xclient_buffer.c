/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 09:20:35 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/16 14:02:39 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_xclient_buffer(t_xclient *xclient)
{
	xclient->buf = mlx_new_image(xclient->mlx, _WIDTH, _HEIGHT);
	if (!xclient->buf)
		(ft_xclient_free(xclient), exit(EXIT_FAILURE));
	xclient->data = mlx_get_data_addr(\
		xclient->buf, &xclient->bpp, &xclient->lsize, &xclient->endian);
}
