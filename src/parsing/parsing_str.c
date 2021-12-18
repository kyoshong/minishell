/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:17:24 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/14 18:26:51 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *str, int start, int end)
{
	int		quote_check;

	quote_check = 0;
	if (!is_quote(str[start], quote_check))
		return (0);
	while (str[start] && start < end + 1)
	{
		if (is_quote(str[start], quote_check))
			quote_check = is_quote(str[start], quote_check);
		if (quote_check == D_CLOSE || quote_check == S_CLOSE)
			return (quote_check);
		start++;
	}
	return (0);
}

int	parsing_quote_str(char *str, int start, int quote)
{
	quote = is_quote(str[start], 0);
	start++;
	while (str[start])
	{
		if (quote < is_quote(str[start], quote))
			break ;
		start++;
	}
	return (start);
}

int	parsing_env_str(char *str, int start)
{
	while (str[start] && (!is_space(str[start + 1]) \
	&& !ft_strchr("|<>", str[start + 1]) && \
	!check_quote(str, start + 1, ft_strlen(str))))
	{
		start++;
	}
	return (start);
}
