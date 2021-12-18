/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:34:49 by ulee              #+#    #+#             */
/*   Updated: 2021/12/16 19:34:49 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strendstr(const char *str, const char *part)
{
	if (str == NULL || part == NULL)
		return (NULL);
	while (*str)
	{
		while (*str && *part && *str == *part)
			part++;
		if (*part == '\0')
			return ((char *)str + ft_strlen(part));
		str++;
	}
	return (NULL);
}
