/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:11:12 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/08 23:42:19 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ft_color_read(const char *str)
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
		return (ft_pstderr(__ERR_7), ft_vec3(nan(""), nan(""), nan("")));
	r = ft_atoi(str);
	g = ft_atoi(s1 + 1);
	b = ft_atoi(s2 + 1);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (ft_pstderr(__ERR_8), ft_vec3(nan(""), nan(""), nan("")));
	return (ft_vec3((1.0 * r) / 255.0, (1.0 * g) / 255.0, (1.0 * b) / 255.0));
}
