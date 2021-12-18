/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:28:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/15 17:20:02 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sh_count_word(char const *s)
{
	int	i;
	int	count;
	int	quote;

	if (ft_strlen(s) < 3)
		return (1);
	i = 0;
	count = 1;
	quote = 0;
	while (s[i])
	{
		if (is_quote(s[i], quote) > 0)
		{
			quote = is_quote(s[i], quote);
			if (quote != S_OPEN || quote != D_OPEN)
				quote = 0;
		}
		if (quote == 0 && check_priority(s, i) > 0)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	sh_make_word(t_bundle *bundle, char const *s, int j, int word_len)
{
	int		i;

	i = 0;
	while (word_len)
		bundle->cmd_line[i++] = s[j - word_len--];
	bundle->cmd_line[i] = '\0';
	return (0);
}

int	cut_cmd(t_bundle *bundles, char const *s, int i, int j)
{
	int	word_len;

	word_len = 0;
	while (s[j])
	{
		if (!is_quote(s[j], bundles[i].quote) && check_priority(s, j))
		{
			bundles[i].priority = check_priority(s, j);
			j += 2;
		}
		while (s[j] && !(!bundles[i].quote && check_priority(s, j)))
		{
			bundles[i].quote = is_quote(s[j++], bundles[i].quote);
			if (bundles[i].quote != S_OPEN || bundles[i].quote != D_OPEN)
				bundles[i].quote = 0;
			word_len++;
		}
		if (set_bundle_line(&bundles[i], word_len))
			return (i);
		word_len = sh_make_word(&bundles[i], s, j, word_len);
		i++;
	}
	return (-1);
}

t_bundle	*split_bundle(char const *str)
{
	int			bundles_num;
	t_bundle	*bundles;
	int			i;

	bundles_num = sh_count_word(str);
	bundles = (t_bundle *)malloc(sizeof(t_bundle) * (bundles_num + 1));
	if (bundles == NULL)
		return (NULL);
	ft_bzero(bundles, sizeof(t_bundle) * (bundles_num + 1));
	bundles[bundles_num].cmd_line = NULL;
	set_bundle(bundles, bundles_num, str);
	i = cut_cmd(bundles, str, 0, 0);
	if (i > -1)
		free_bundle(bundles);
	return (bundles);
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
