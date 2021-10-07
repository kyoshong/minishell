#include "minishell.h"

void	parsing(char *str)
{
	char	**space;
	int		i;

	space = ft_split(str, ' ');
	if (space == NULL)
		print_error("SPACE_SPLIT_ERROR");
	i = 0;
	while (space[i])
		printf("%s\n", space[i++]);
}

void	split_command(char *str)
{
	char	**semi;
	int		i;

	semi = ft_split(str, ';');
	if (semi == NULL)
		print_error("SEMI_SPLIT_ERROR");
	i = 0;
	while(semi[i])
		parsing(semi[i++]);
}

void 	ctrl_c(int sig)
{
	write(1, "\n", 1);
	print_prompt(g_env);
	signal(SIGINT, ctrl_c);
}

int		main(int ac, char **av, char **env)
{
	char *input;
	char *line;

	g_env = env;
	while(1)
	{
		signal(SIGINT, ctrl_c);
		print_prompt(env);
		get_next_line(0, &line);
		split_command(line);
		// printf("%s\n", input);
	}

}
