/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:29:05 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/19 00:33:50 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_isfloat(const char *nptr)
{
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	if (!ft_isdigit(*nptr))
		return (false);
	while (ft_isdigit(*nptr))
		++nptr;
	if (*nptr == '.')
		++nptr;
	while (ft_isdigit(*nptr))
		++nptr;
	if (*nptr)
		return (false);
	return (true);
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
	int		i;
	float	d;

	if (!ft_isfloat(nptr))
		return (NAN);
	f = ft_atoi(nptr);
	s = ft_strchr(nptr, '.');
	if (!s)
		return (f);
	i = ft_atoi(s + 1);
	d = (1.0F / powf(10.0F, ft_intlenf(i))) * i;
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '-')
		return (f - d);
	return (f + d);
}
