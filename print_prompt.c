#include "minishell.h"

char *get_homepath(char **env)
{
	int i;
	char **split;
	char *ret;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME", 4) == 0)
		{
			split = ft_split(env[i], '=');
			ret = ft_strdup(split[1]);
			two_free(split);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char *cut_path(char *path_home, char *path_curr)
{
	int len_homepath;

	len_homepath = ft_strlen(path_home);
	return (&path_curr[len_homepath]);
}

void print_prompt(char **env)
{
	char *path_home;
	char *path_current;
	char	buff[4097];
	char *prompt;
	char *input;

	path_home = get_homepath(env);
	path_current = getcwd(buff, 4097);
	if (ft_strncmp(path_home, path_current, ft_strlen(path_home)) == 0)
		ft_printf("~%s : ", cut_path(path_home, path_current));
	else
		ft_printf("%s : ", path_current);
}
