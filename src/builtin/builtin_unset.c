/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:18:19 by ulee              #+#    #+#             */
/*   Updated: 2021/12/16 15:42:47 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**arr_cpy(t_token *token, int len)
{
	int		i;
	int		k;
	char	**key;
	char	**env_copy;

	i = 0;
	k = 0;
	env_copy = (char **)malloc(sizeof(char *) * len);
	if (env_copy == NULL)
		return (NULL);
	env_copy[len - 1] = NULL;
	while (g_global.env[i])
	{
		key = ft_split(g_global.env[i], '=');
		if (key == NULL)
			return (NULL);
		if (ft_strcmp(key[0], token->content))
		{
			env_copy[k] = ft_strdup(g_global.env[i]);
			k++;
		}
		i++;
		ft_two_free(key);
	}
	return (env_copy);
}

int	invalid_argument(t_bundle *bundle, int *result)
{
	if (ft_strchr(bundle->token->content, '='))
	{
		*result = INVALID_ARG;
		printf("minishell: unset: %s: not a valid identifier\n", \
		bundle->token->content);
		return (1);
	}
	return (0);
}

int	builtin_unset(t_bundle *bundle)
{
	char	**env_copy;
	char	*env_current;
	char	**temp;
	int		result;

	result = SUCCESS;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		if (invalid_argument(bundle, &result))
			continue ;
		env_current = builtin_getenv(bundle->token->content);
		if (env_current)
		{
			ft_free(env_current);
			env_copy = arr_cpy(bundle->token, ft_arrlen(g_global.env));
			if (env_copy == NULL)
				return (FAIL);
			temp = g_global.env;
			g_global.env = env_copy;
			ft_two_free(temp);
		}
	}
	return (result);
}
