/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:29:05 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/13 15:40:17 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_isfloat(const char *nptr)
{
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	if (!ft_isdigit(*nptr))
		return (0);
	while (ft_isdigit(*nptr))
		++nptr;
	if (*nptr == '.')
		++nptr;
	while (ft_isdigit(*nptr))
		++nptr;
	if (*nptr)
		return (0);
	return (1);
}

static float	ft_intlenf(int n)
{
	float			lenf;
	unsigned int	i;

	lenf = 0.0F;
	i = n;
	if (!n)
		lenf += 1.0F;
	else if (n < 0)
	{
		lenf += 1.0F;
		i = -n;
	}
	while (i > 0)
	{
		lenf += 1.0F;
		i = i / 10;
	}
	return (lenf);
}

float	ft_atof(const char *nptr)
{
	float	f;
	char	*s;
	float	d;

	if (!ft_isfloat(nptr))
		return (nanf(""));
	f = ft_atoi(nptr);
	s = ft_strchr(nptr, '.');
	if (!s)
		return (f);
	d = ft_atoi(s + 1);
	d /= powf(10.0F, ft_intlenf(d));
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '-')
		return (f - d);
	return (f + d);
}
