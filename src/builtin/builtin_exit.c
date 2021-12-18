/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:15:14 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 16:14:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isallnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(t_bundle *bundle)
{
	write(2, "exit\n", 5);
	if (bundle->token->next)
	{
		if (!ft_isallnum(bundle->token->next->content))
		{
			printf("bash: exit: %s: numeric argument required\n", \
				bundle->token->next->content);
		}
		exit(ft_atoi(bundle->token->next->content));
	}
	exit(0);
}
