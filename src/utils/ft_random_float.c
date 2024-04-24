/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:06:22 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/20 19:10:39 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	ft_random_float(float const min, float const max)
{
	static float const	rand_max_reciprocal = 1.0F / (RAND_MAX + 1.0F);

	return (min + (max - min) * rand() * rand_max_reciprocal);
}
