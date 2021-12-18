/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:34:15 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 10:25:47 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_exit(char *str, int error_num)
{
	printf("%s\n", str);
	exit(error_num);
}

void	print_not_found(char *cmd, int status)
{
	char	log[300];
	char	*process;
	char	*detail;

	ft_memset(log, 0, 300);
	process = "minishell: ";
	if (status == 512)
		detail = ": command not found\n";
	else if (status == -1)
		detail = ": No such file or directory\n";
	ft_strlcat(log, process, ft_strlen(process) + 1);
	ft_strlcat(log, cmd, ft_strlen(process) + ft_strlen(cmd) + 1);
	ft_strlcat(log, detail, ft_strlen(process) + ft_strlen(cmd) + \
		ft_strlen(detail) + 1);
	write(2, log, ft_strlen(log));
}
