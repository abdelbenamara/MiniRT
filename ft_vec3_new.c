/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:55:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/21 20:18:29 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	*ft_vec3_new(const char *str)
{
	char	*s1;
	char	*s2;
	t_vec3	*u;

	s1 = ft_strchr(str, ',');
	s2 = NULL;
	if (s1)
		s2 = ft_strchr(s1 + 1, ',');
	if (!s2 || ft_strchr(s2 + 1, ','))
		return (ft_pstderr(__ERR_9), NULL);
	u = malloc(sizeof(t_vec3));
	if (!u)
		return (ft_pstderr(__ERR_2), NULL);
	*s1 = '\0';
	u->x = ft_atof(str);
	*s1 = ',';
	*s2 = '\0';
	u->y = ft_atof(s1 + 1);
	*s2 = ',';
	u->z = ft_atof(s2 + 1);
	if (isnan(u->x) || isnan(u->y) || isnan(u->z))
		return (ft_pstderr(__ERR_5), free(u), NULL);
	return (u);
}
