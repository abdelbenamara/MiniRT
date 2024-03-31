/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:55:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 13:52:54 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_vec3f_read(char const *str)
{
	char			*comma[2];
	t_vec3f			u;

	comma[0] = ft_strchr(str, ',');
	comma[1] = NULL;
	if (comma[0])
		comma[1] = ft_strchr(comma[0] + 1, ',');
	if (!comma[1] || ft_strchr(comma[1] + 1, ','))
		return (ft_pstderr(__ERR_9), ft_vec3f(NAN, NAN, NAN));
	*comma[0] = '\0';
	u.x = ft_atof(str);
	*comma[0] = ',';
	*comma[1] = '\0';
	u.y = ft_atof(comma[0] + 1);
	*comma[1] = ',';
	u.z = ft_atof(comma[1] + 1);
	if (isnan(u.x) || isnan(u.y) || isnan(u.z))
		return (ft_pstderr(__ERR_5), ft_vec3f(NAN, NAN, NAN));
	return (u);
}
