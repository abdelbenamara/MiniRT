/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:29:05 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/03 01:00:50 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	ft_float_parse(char const **nptr, float *nexp)
{
	float	f;

	f = 0.0F;
	*nexp = 0.0F;
	while (ft_isdigit(**nptr))
	{
		f = f * 10.0F + (**nptr - '0');
		++(*nptr);
		*nexp -= 1.0F;
	}
	return (f);
}

float	ft_str_to_float(char const *nptr)
{
	float	sign;
	float	nexp;
	float	i;
	float	d;

	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	sign = 1.0F;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1.0F;
		++nptr;
	}
	if (!ft_isdigit(*nptr))
		return (NAN);
	i = ft_float_parse(&nptr, &nexp);
	if (*nptr == '.')
		++nptr;
	d = ft_float_parse(&nptr, &nexp);
	if (*nptr)
		return (NAN);
	return (copysignf(i + d * powf(10.0F, nexp), sign));
}
