/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:55:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 15:58:24 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ft_vec3_read(const char *str)
{
	const t_color	err = ft_vec3(nanf(""), nanf(""), nanf(""));
	char			*comma[2];
	t_vec3			u;

	comma[0] = ft_strchr(str, ',');
	comma[1] = NULL;
	if (comma[0])
		comma[1] = ft_strchr(comma[0] + 1, ',');
	if (!comma[1] || ft_strchr(comma[1] + 1, ','))
		return (ft_pstderr(__ERR_9), err);
	*comma[0] = '\0';
	u.x = ft_atof(str);
	*comma[0] = ',';
	*comma[1] = '\0';
	u.y = ft_atof(comma[0] + 1);
	*comma[1] = ',';
	u.z = ft_atof(comma[1] + 1);
	if (isnanf(u.x) || isnanf(u.y) || isnanf(u.z))
		return (ft_pstderr(__ERR_5), err);
	return (u);
}
