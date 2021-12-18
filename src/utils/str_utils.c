/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:36:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/17 15:51:55 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s, int start)
{
	char	*result;
	int		len;

	len = ft_strlen(s) - start;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (start < len)
	{
		result[start] = s[start];
		start++;
	}
	result[len] = 0;
	return (result);
}

int	ft_isallblank(char *str)
{
	if (!ft_strcmp(str, ""))
		return (1);
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

char	*join_env_str(char *content, char *env, int start)
{
	char	*pre;
	char	*new_content;

	if ((start - 1) > 0)
		pre = ft_substr(content, 0, start - 1);
	else
		pre = NULL;
	new_content = ft_strjoin(pre, env);
	ft_free(env);
	ft_free(pre);
	return (new_content);
}

void	make_env_str(int *start, int *end, t_token *token)
{
	char	*new_content;
	char	*env;
	char	*temp;

	*end = *start;
	while (token->content[*end] && !is_vaild_char(token->content[*end]))
		*end += 1;
	temp = ft_substr(token->content, *start, *end - *start);
	env = builtin_getenv(temp);
	new_content = join_env_str(token->content, env, *start);
	ft_free(temp);
	*start = ft_strlen(new_content);
	temp = ft_substr(token->content, *end, ft_strlen(token->content));
	env = ft_strjoin(new_content, temp);
	ft_free(new_content);
	ft_free(temp);
	ft_free(token->content);
	token->content = env;
}

char	*ft_strnstr_reverse(char *check_in_file, t_list *checks_dup)
{
	while (check_in_file != NULL)
	{
		if (*(++check_in_file) == '\0')
			return (check_in_file);
		check_in_file = ft_strnstr(check_in_file, checks_dup->content, \
			ft_strlen(check_in_file));
		if (check_in_file == NULL)
			return (NULL);
	}
	return (NULL);
}
