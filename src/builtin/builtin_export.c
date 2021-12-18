/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:15:22 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 17:20:56 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_env(t_token *token)
{
	int		len;
	int		i;
	char	**env_copy;
	char	**temp;

	len = ft_arrlen(g_global.env);
	if (len == 0)
		return ;
	env_copy = (char **)malloc(sizeof(char *) * (len + 2));
	if (env_copy == NULL)
		return ;
	env_copy[len + 1] = NULL;
	env_copy[len] = ft_strdup(token->content);
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(g_global.env[i]);
		i++;
	}
	temp = g_global.env;
	g_global.env = env_copy;
	ft_two_free(temp);
}

void	replace_env(t_token *token, char *key)
{
	int		i;
	char	**env_split;
	char	*temp;

	i = 0;
	while (g_global.env[i])
	{
		env_split = ft_split(g_global.env[i], '=');
		if (env_split == NULL)
			return ;
		if (ft_strcmp(env_split[0], key) == 0)
		{
			ft_two_free(env_split);
			temp = g_global.env[i];
			g_global.env[i] = ft_strdup(token->content);
			ft_free(temp);
			return ;
		}
		ft_two_free(env_split);
		i++;
	}
}

void	print_env(void)
{
	int		i;
	char	*env_line;

	i = 0;
	while (g_global.env[i])
	{
		env_line = ft_strjoin("declare -x ", g_global.env[i]);
		printf("%s\n", env_line);
		ft_free(env_line);
		i++;
	}
}

int	valid_argument(t_bundle *bundle, int *result)
{
	if (ft_strchr(bundle->token->content, '=') == NULL)
	{
		if (*result != INVALID_ARG)
			*result = SUCCESS;
		return (0);
	}
	if (!ft_strncmp(bundle->token->content, "=", 1))
	{
		*result = INVALID_ARG;
		printf("minishell: export: %s: not a valid identifier\n", \
		bundle->token->content);
		return (0);
	}
	return (1);
}

int	builtin_export(t_bundle *bundle)
{
	char	**content_split;
	char	*env_value;
	int		result;

	result = SUCCESS;
	if (bundle->token->next == NULL)
		print_env();
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		if (!valid_argument(bundle, &result))
			continue ;
		content_split = ft_split(bundle->token->content, '=');
		if (content_split == NULL)
			return (FAIL);
		env_value = builtin_getenv(content_split[0]);
		if (env_value)
			replace_env(bundle->token, content_split[0]);
		else
			append_env(bundle->token);
		ft_free(env_value);
		all_free(content_split);
	}
	return (result);
}
