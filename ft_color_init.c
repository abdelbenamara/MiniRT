/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:11:12 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 15:09:28 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_color_init(const char *str)
{
	char	*s1;
	char	*s2;
	int		r;
	int		g;
	int		b;

	s1 = ft_strchr(str, ',');
	s2 = NULL;
	if (s1)
		s2 = ft_strchr(s1 + 1, ',');
	if (!s2 || ft_strchr(s2 + 1, ','))
		return (ft_pstderr(__ERR_7), -1);
	r = ft_atoi(str);
	g = ft_atoi(s1 + 1);
	b = ft_atoi(s2 + 1);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (ft_pstderr(__ERR_8), -1);
	return (r << 16 | g << 8 | b);
}
