/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclient_flush.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 09:50:56 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/04 17:52:10 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_xclient_flush(t_xclient *xclient)
{
	void	*tmp;

	tmp = xclient->img;
	xclient->img = xclient->buf;
	if (tmp)
		mlx_destroy_image(xclient->mlx, tmp);
	xclient->update = 1;
}
