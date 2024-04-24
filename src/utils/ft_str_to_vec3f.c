/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_vec3f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:55:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/23 20:49:13 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3f	ft_str_to_vec3f(char const *str)
{
	char			*comma[2];
	t_vec3f			u;

	comma[0] = ft_strchr(str, ',');
	comma[1] = NULL;
	if (comma[0])
		comma[1] = ft_strchr(comma[0] + 1, ',');
	if (!comma[1] || ft_strchr(comma[1] + 1, ','))
		return (ft_pstderr(__ERR_14), ft_vec3f(NAN, NAN, NAN));
	*comma[0] = '\0';
	u.x = ft_str_to_float(str);
	*comma[0] = ',';
	*comma[1] = '\0';
	u.y = ft_str_to_float(comma[0] + 1);
	*comma[1] = ',';
	u.z = ft_str_to_float(comma[1] + 1);
	if (!isfinite(u.x) || !isfinite(u.y) || !isfinite(u.z))
		return (ft_pstderr(__ERR_09), ft_vec3f(NAN, NAN, NAN));
	return (u);
}
