/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:40:42 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/16 20:13:24 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir_token(t_token *token)
{
	return (token->token_type >= REDIR_IN && token->token_type <= D_REDIR_OUT);
}

int	is_io_token(t_token *token)
{
	return (token->token_type >= REDIR_IN);
}

void	check_env_token(t_token *token)
{
	int	start;
	int	end;

	if (ft_strlen(token->content) < 2)
		return ;
	start = 1;
	while (token->content[start])
	{
		if (token->content[start - 1] == '$' && \
		!is_vaild_char(token->content[start]))
		{
			make_env_str(&start, &end, token);
		}
		start++;
	}
}

void	replace_env_token(t_bundle *bundle, t_token *temp)
{
	char	*env_tem;

	env_tem = builtin_getenv(temp->content);
	if (env_tem == NULL)
	{
		if (bundle->head == temp)
		{
			bundle->head = NULL;
		}
		tokenlst_delete(temp);
	}
	else
	{
		ft_free(temp->content);
		temp->content = env_tem;
	}
}
