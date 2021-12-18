/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:17:51 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 10:33:39 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	*ret_pwd;
	char	dir[1000];
	char	*ret;

	ret_pwd = getcwd(dir, 1000);
	if (ret_pwd == 0)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	ret = ft_strdup(ret_pwd);
	return (ret);
}

int	builtin_pwd(t_bundle *bundle)
{
	char	*ret_pwd;

	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
	}
	ret_pwd = get_pwd();
	printf("%s\n", ret_pwd);
	ft_free(ret_pwd);
	return (SUCCESS);
}
