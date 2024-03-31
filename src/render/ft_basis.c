/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:07:39 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/30 16:09:39 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_basis	ft_basis(t_vec3f const x, t_vec3f const y, t_vec3f const z)
{
	t_basis	basis;

	basis.x = x;
	basis.y = y;
	basis.z = z;
	return (basis);
}
