/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_getenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:17:10 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 15:41:40 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*builtin_getenv(char *key)
{
	int		i;
	char	*equal;
	char	*env_key;
	char	*env_value;

	if (key[1] == '?')
		return (ft_itoa(g_global.status));
	i = 0;
	while (g_global.env[i])
	{
		equal = ft_strchr(g_global.env[i], '=');
		env_key = ft_substr(g_global.env[i], 0, equal - g_global.env[i]);
		env_value = equal + 1;
		if (*env_value == '\0')
			env_value = "";
		if (ft_strcmp(env_key, key) == 0)
		{
			ft_free(env_key);
			return (ft_strdup(env_value));
		}
		ft_free(env_key);
		i++;
	}
	return (NULL);
}
