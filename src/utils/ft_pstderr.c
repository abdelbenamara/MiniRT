/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pstderr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:17:12 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/24 13:52:54 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

ssize_t	ft_pstderr(char const *str)
{
	return (write(STDERR_FILENO, str, ft_strlen(str) * sizeof(char)));
}
