/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:13:28 by ulee              #+#    #+#             */
/*   Updated: 2021/12/21 05:12:00 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_bundle *bundle)
{
	int	i;

	if (bundle->token->next && \
		!ft_strncmp(bundle->token->next->content, "=", 1))
	{
		bundle->token = bundle->token->next;
		printf("minishell: env: %s: not a valid identifier\n", \
		bundle->token->content);
		return (INVALID_ARG);
	}
	if (bundle->token->next && bundle->token->next->token_type < ENV)
	{
		printf("minishell: env: %s: No such file or directory\n", \
			bundle->token->next->content);
		return (FAIL);
	}
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
		bundle->token = bundle->token->next;
	i = 0;
	while (g_global.env[i])
		printf("%s\n", g_global.env[i++]);
	return (SUCCESS);
}

char	**dup_env(char **envp)
{
	char	**env;
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
