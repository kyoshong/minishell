/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 02:23:14 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/16 20:12:15 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token(t_bundle *bnde, int i, int start)
{
	int	token_type;
	int	back_space;

	bnde->quote = 0;
	back_space = FALSE;
	while (bnde->cmd_line[i])
	{
		token_type = check_vaild_str(bnde->cmd_line, i);
		if (token_type > 0)
		{
			i = set_token_type(token_type, bnde, i);
			break ;
		}
		i++;
	}
	if ((bnde->cmd_line[i] && is_space(bnde->cmd_line[i + 1])) \
	|| !bnde->cmd_line[i])
		back_space = TRUE;
	tokenlst_add_back(&bnde->token, tokenlst_new(make_token \
	(bnde->cmd_line, start, i, token_type), token_type, back_space));
	return (i);
}

int	check_redir_token(t_token *temp)
{
	int	error;

	error = 0;
	if (temp->next == NULL || is_space_str(temp->next->content))
	{
		error = \
		printf("minishell: syntax error near unexpected token 'newline'\n");
	}
	else if (temp->next->token_type >= REDIR_IN)
	{
		error = printf("minishell: syntax error near \
		unexpected token '%s'\n", temp->next->content);
	}
	set_fd(temp);
	return (error);
}

int	check_vaild_token_list(t_bundle *bundle, int error)
{
	t_token	*temp;
	int		size;

	temp = bundle->token;
	size = tokenlst_size(bundle->token);
	while (temp)
	{
		if (is_redir_token(temp))
		{
			check_redir_token(temp);
			bundle->is_redir = 1;
		}
		else if (temp->token_type == PIPE && bundle->head == temp)
			error = \
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (temp->token_type == D_CLOSE)
			check_env_token(temp);
		else if (temp->token_type == ENV)
			replace_env_token(bundle, temp);
		if (error)
			return (FAIL);
		temp = temp->next;
	}
	return (SUCCESS);
}

int	parsing_token_list(t_bundle *bundle)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (bundle->cmd_line[i])
	{
		while (bundle->cmd_line[i] && is_space(bundle->cmd_line[i]))
			i++;
		if (!bundle->cmd_line[i])
			break ;
		start = i;
		i = get_token(bundle, i, start);
		set_iotoken(bundle);
		i++;
	}
	bundle->head = bundle->token;
	if (check_vaild_token_list(bundle, 0) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	parsing_token(t_bundle *bundles)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line)
	{
		bundles[i].quote = 0;
		if (parsing_token_list(&bundles[i]) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
