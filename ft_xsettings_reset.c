/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xsettings_reset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:22:32 by abenamar          #+#    #+#             */
/*   Updated: 2023/12/30 22:57:42 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_xsettings_reset(t_xsettings *xsettings)
{
	xsettings->origin.x = WIDTH / 2;
	xsettings->origin.y = HEIGHT / 2;
	xsettings->theta.x = -35.0;
	xsettings->theta.y = 0.0;
	xsettings->theta.z = -45.0;
}
