/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bundles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:58:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/15 17:19:56 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_bundle_line(t_bundle *bundle, int word_len)
{
	int		i;
	char	*tem;

	i = 0;
	tem = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!tem)
		return (1);
	bundle->cmd_line = tem;
	return (0);
}

void	set_bundle(t_bundle *bundle, int bundles_num, char const *str)
{
	int		i;

	i = 0;
	while (i <= bundles_num)
	{
		bundle[i].input = (char *)str;
		i++;
	}
}
