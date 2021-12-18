/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:09:39 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 16:50:14 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home_destpath(char *dest_path)
{
	char	*home_path;
	char	*temp;

	home_path = builtin_getenv("HOME");
	temp = dest_path;
	dest_path = ft_strjoin(home_path, ++dest_path);
	ft_free(home_path);
	ft_free(temp);
	return (dest_path);
}

int	builtin_cd(t_bundle *bundle)
{
	int		ret_chdir;
	char	*dest_path;

	if (!bundle->token->next)
		dest_path = builtin_getenv("HOME");
	else
		dest_path = ft_strdup(bundle->token->next->content);
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
		bundle->token = bundle->token->next;
	if (!ft_strncmp(dest_path, "~", 1))
		dest_path = get_home_destpath(dest_path);
	ret_chdir = chdir(dest_path);
	if (ret_chdir == -1)
	{
		printf("bash: cd: %s: %s\n", dest_path, strerror(errno));
		ft_free(dest_path);
		return (INVALID_ARG);
	}
	ft_free(dest_path);
	return (SUCCESS);
}
