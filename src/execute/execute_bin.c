/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:19:25 by ulee              #+#    #+#             */
/*   Updated: 2021/12/18 16:07:46 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_cmd(char *cmd, char **arr)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		execve(cmd, arr, g_global.env);
		exit(2);
	}
	waitpid(pid, &status, 0);
	return (status);
}

int	execute_bin(t_bundle *bundle)
{
	char	**arg_arr;
	char	*cmd;
	int		result;

	cmd = ft_strdup(bundle->token->content);
	arg_arr = execute_make_arr(bundle);
	if (ft_strchr(cmd, '/'))
		result = run_cmd(cmd, arg_arr);
	else
		result = execute_run_paths(cmd, arg_arr);
	if (result == -1 || result == 512)
		print_not_found(cmd, result);
	ft_free(cmd);
	ft_two_free(arg_arr);
	return (result);
}
