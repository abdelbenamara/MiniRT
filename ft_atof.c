/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:29:05 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/20 23:53:01 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_isdouble(const char *nptr)
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

static size_t	ft_intlen(int n)
{
	size_t			len;
	unsigned int	i;

	len = 0;
	i = n;
	if (!n)
		++len;
	else if (n < 0)
	{
		++len;
		i = -n;
	}
	while (i > 0)
	{
		++len;
		i = i / 10;
	}
	return (len);
}

double	ft_atof(const char *nptr)
{
	double	d;
	char	*s;
	int		i;

	if (!ft_isdouble(nptr))
		return (nan(""));
	d = ft_atoi(nptr);
	s = ft_strchr(nptr, '.');
	if (!s)
		return (d);
	i = ft_atoi(s + 1);
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	return (d + (1.0 - 2.0 * (*nptr == '-')) * i / pow(10.0, ft_intlen(i)));
}
