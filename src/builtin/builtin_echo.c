/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:12:10 by ulee              #+#    #+#             */
/*   Updated: 2021/12/15 15:27:11 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_arg(t_bundle *bundle, char *buf)
{
	char	*temp;
	char	*ret;

	ret = ft_strjoin(buf, bundle->token->content);
	if (ret == NULL)
		return (NULL);
	if (bundle->token->next && bundle->token->back_space)
	{
		temp = ret;
		ret = ft_strjoin(ret, " ");
		if (ret == NULL)
			return (NULL);
		ft_free(temp);
	}
	return (ret);
}

int	find_n_option(char *content)
{
	int	i;

	if (!ft_strncmp(content, "-n", 2))
	{
		if (ft_strlen(content) > 2)
		{
			i = 2;
			while (content[i])
			{
				if (content[i] != 'n' && content[i] != 'e')
					return (0);
				i++;
			}
		}
		return (1);
	}
	return (0);
}

void	print_echo(char *print_word, int n_option)
{
	if (print_word)
	{
		write(1, print_word, ft_strlen(print_word));
		ft_free(print_word);
	}
	if (n_option == 0)
		write(1, "\n", 1);
}

int	builtin_echo(t_bundle *bundle)
{
	int		n_option;
	char	*print_word;
	char	*temp;

	n_option = 0;
	print_word = NULL;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		if (find_n_option(bundle->token->content) && !print_word)
			n_option = 1;
		else
		{
			temp = print_word;
			print_word = append_arg(bundle, print_word);
			if (print_word == NULL)
				return (FAIL);
			ft_free(temp);
		}
	}
	print_echo(print_word, n_option);
	return (SUCCESS);
}
