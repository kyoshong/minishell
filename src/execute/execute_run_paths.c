/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:22:52 by ulee              #+#    #+#             */
/*   Updated: 2021/12/16 19:32:25 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_pathlist(void)
{
	char	*path_env;
	char	**path_list;

	path_env = builtin_getenv("PATH");
	if (path_env == NULL)
	{
		ft_free(path_env);
		return (NULL);
	}
	path_list = ft_split(path_env, ':');
	ft_free(path_env);
	return (path_list);
}

char	*make_fullpath(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	ft_free(temp);
	return (full_path);
}

int	execute_run_paths(char *cmd, char **arg_arr)
{
	char	**path_list;
	int		i;
	char	*full_path;
	int		status;

	path_list = make_pathlist();
	if (path_list == NULL)
		return (-1);
	i = 0;
	while (path_list[i])
	{
		full_path = make_fullpath(path_list[i], cmd);
		status = run_cmd(full_path, arg_arr);
		ft_free(full_path);
		if (status == 3 || status == 0 || status == 2 || \
			status == 256 || status == 32512 || status == -1)
		{
			ft_two_free(path_list);
			return (status);
		}
		i++;
	}
	ft_two_free(path_list);
	return (status);
}
