/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:21 by ulee              #+#    #+#             */
/*   Updated: 2021/11/01 22:29:30 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	if (len == 0)
		return (0);
	i = 0;
	while (i < (len - 1) && first[i] && second[i])
	{
		if (first[i] != second[i])
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}
