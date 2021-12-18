/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:35:19 by ulee              #+#    #+#             */
/*   Updated: 2021/12/16 19:35:19 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_two_free(char **result)
{
	int		i;

	if (result == NULL)
		return ;
	i = 0;
	while (result[i] != NULL)
	{
		ft_free(result[i]);
		result[i] = NULL;
		i++;
	}
	ft_free(result);
	return ;
}
