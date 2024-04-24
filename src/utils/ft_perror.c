/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:01:22 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 04:01:14 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_perror(char const *str)
{
	char	*s;

	s = ft_strjoin("Error: ", str);
	if (!s)
		return (ft_pstderr(__ERR_07), perror(str));
	return (perror(s), free(s));
}
