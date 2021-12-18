/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:23:46 by ulee              #+#    #+#             */
/*   Updated: 2021/12/14 21:11:12 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_list_file(void)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	t_list			*files;

	dir_ptr = opendir(".");
	file = readdir(dir_ptr);
	files = NULL;
	while (file)
	{
		if (ft_strncmp(file->d_name, ".", 1) != 0)
			ft_lstadd_back(&files, ft_lstnew(ft_strdup(file->d_name)));
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (files);
}

t_list	*get_list_check(char *cmd)
{
	t_list	*checks;
	int		start;
	char	*word;
	int		i;

	checks = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '*')
		{
			ft_lstadd_back(&checks, ft_lstnew(ft_strdup("*")));
			while (cmd[i] && cmd[i] == '*')
				i++;
		}
		else
		{
			start = i;
			while (cmd[i] && cmd[i] != '*')
				i++;
			word = ft_substr(cmd, start, i - start);
			ft_lstadd_back(&checks, ft_lstnew(word));
		}
	}
	return (checks);
}

char	*check_valid(char *file_name, t_list *checks, t_list *head)
{
	char	*check_in_file;

	check_in_file = ft_strnstr(file_name, checks->content, \
		ft_strlen(file_name));
	if (!check_in_file)
		return (NULL);
	check_in_file = check_in_file + ft_strlen(checks->content);
	if (checks == head)
	{
		if (ft_strncmp(file_name, checks->content, \
			ft_strlen(checks->content)) != 0)
			return (NULL);
		file_name = check_in_file;
		return (file_name);
	}
	if (checks->next == NULL)
	{
		check_in_file = ft_strnstr_reverse(check_in_file, checks);
		if (check_in_file == NULL)
			return (NULL);
		return (check_in_file);
	}
	file_name = check_in_file;
	return (file_name);
}

t_list	*get_list_needfile(t_list *files, t_list *checks)
{
	t_list	*checks_dup;
	t_list	*ret;
	char	*files_content;

	ret = NULL;
	while (files)
	{
		checks_dup = checks;
		files_content = files->content;
		while (checks_dup)
		{
			if (ft_strcmp(checks_dup->content, "*") != 0)
			{
				files_content = check_valid(files_content, checks_dup, checks);
				if (files_content == NULL)
					break ;
			}
			checks_dup = checks_dup->next;
		}
		if (checks_dup == NULL)
			ft_lstadd_back(&ret, ft_lstnew(ft_strdup(files->content)));
		files = files->next;
	}
	return (ret);
}

t_list	*execute_wildcard(char *token_content)
{
	t_list	*files;
	t_list	*checks;
	t_list	*ret;

	files = get_list_file();
	checks = get_list_check(token_content);
	ret = get_list_needfile(files, checks);
	if (ret == NULL)
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup(token_content)));
	ft_lstclear(&files);
	ft_lstclear(&checks);
	return (ret);
}
