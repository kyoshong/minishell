/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:07:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/18 16:10:05 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# define TRUE 1
# define FALSE 0
# define D_OPEN 1
# define S_OPEN 2
# define S_CLOSE 10
# define D_CLOSE 11
# define ENV 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define D_REDIR_IN 6
# define D_REDIR_OUT 7
# define PIPE 8
# define STATUS 9
# define P_OR 1
# define P_AND 2
# define SUCCESS 0
# define FAIL 1
# define NO_BUILTIN 10
# define INVALID_ARG 11

typedef struct s_global
{
	int		status;
	char	**env;
}				t_global;

t_global	g_global;

typedef struct s_token
{
	struct s_token	*pre;
	struct s_token	*next;
	int				pipe;
	int				redir;
	int				fd[2];
	char			*content;
	int				token_type;
	int				back_space;

}				t_token;

typedef struct s_bundle
{
	t_token		*token;
	t_token		*head;
	int			quote;
	int			priority;
	int			is_pipe;
	int			is_redir;
	char		*cmd_line;
	char		**env;
	t_token		*pipe_token;
	char		*input;
	char		*error_msg;
}				t_bundle;

// main
void		init_main(int argc, char **av, char **env);
void		start_sh(char *input);
char		**dup_env(char **envp);

//builtin
char		*get_home_destpath(char *dest_path);
int			builtin_cd(t_bundle *bundle);

char		*append_arg(t_bundle *bundle, char *buf);
int			find_n_option(char *content);
void		print_echo(char *print_word, int n_option);
int			builtin_echo(t_bundle *bundle);

int			builtin_env(t_bundle *bundle);

int			ft_isallnum(char *str);
int			builtin_exit(t_bundle *bundle);

void		append_env(t_token *token);
void		replace_env(t_token *token, char *key);
void		print_env(void);
int			valid_argument(t_bundle *bundle, int *result);
int			builtin_export(t_bundle *bundle);

char		*builtin_getenv(char *key);
int			builtin_pwd(t_bundle *bundle);

char		**arr_cpy(t_token *token, int len);
int			invalid_argument(t_bundle *bundle, int *result);
int			builtin_unset(t_bundle *bundle);

//execute
int			run_cmd(char *cmd, char **arr);
int			execute_bin(t_bundle *bundle);

int			execute_builtin(t_bundle *bundle);

void		handle_ps(int child_ps, t_bundle *bundle, int result);
void		reset_fd(t_bundle *bundle);
int			execute_pipe_cmd(t_bundle *bundle);
int			set_status(int result);
int			execute_cmd(t_bundle *bundle);

t_list		*make_list(t_bundle *bundle);
char		**make_arr(char *cmd, t_list *list);
char		**execute_make_arr(t_bundle *bundle);

char		**make_pathlist(void);
char		*make_fullpath(char *path, char *cmd);
void		print_not_found(char *cmd, int status);
int			execute_run_paths(char *cmd, char **arg_arr);

t_list		*get_list_file(void);
t_list		*get_list_check(char *cmd);
char		*check_valid(char *file_name, t_list *checks, t_list *head);
t_list		*get_list_needfile(t_list *files, t_list *checks);
t_list		*execute_wildcard(char *token_content);

//exit
void		free_bundle(t_bundle *bundles);
void		child_exit(t_bundle *bundles, int status);

void		print_error_exit(char *str, int error_num);

//iohandler
int			pipe_cmd(t_bundle *bundle);

void		get_readline(int fd[], t_token *token);
int			read_here_document(t_bundle *bundle, t_token *token);
void		set_fd(t_token *token);
int			redir_handler(t_bundle *bundle, t_token *token, int err_flag);
int			set_redir_fd(t_bundle *bundle, t_token *token);

int			d_redir_in(t_bundle *bundle, t_token *token);
int			d_redir_out(t_bundle *bundle, t_token *token, int err_flag);
int			redir_out(t_bundle *bundle, t_token *token, int err_flag);
int			redir_in(t_bundle *bundle, t_token *token, int err_flag);

//parsing
int			set_bundle_line(t_bundle *bundle, int word_len);
void		set_bundle(t_bundle *bundle, int bundles_num, char const *str);

int			check_quote(char *str, int start, int end);
int			parsing_quote_str(char *str, int start, int quote);
int			parsing_env_str(char *str, int start);

int			get_token(t_bundle *bnde, int i, int start);
int			check_vaild_token_list(t_bundle *bundle, int error);
int			parsing_token_list(t_bundle *bundle);
int			parsing_token(t_bundle *bundles);

void		set_iotoken(t_bundle *bundle);
int			set_token_type(int token_type, t_bundle *bnde, int i);
char		*make_token(char *str, int start, int end, int token_type);

//signal
void		ctrl_c__no_process(void);
void		ctrl_c__yes_process(void);
void		ctrl_slash__yes_process(void);
void		ctrl_slash__no_process(void);
void		sig_handler(int signum);

void		set_signal(void);
void		unset_signal(int signum);
void		init_signal(int signum);

//utils
int			is_fdnum(char *str, int back);
void		dup_redir_fd(t_bundle *bundle);
t_token		*tokenlst_new(char *content, int token_type, int back_space);
void		tokenlst_delete(t_token *lst);
void		tokenlst_add_back(t_token **lst, t_token *new_token);
void		tokenlst_clear(t_token *lst);
int			tokenlst_size(t_token *lst);
t_token		*tokenlst_last(t_token *lst);
void		make_env_str(int *start, int *end, t_token *token);
int			sh_count_word(char const *s);
int			sh_make_word(t_bundle *bundle, char const *s, int j, int word_len);
int			cut_cmd(t_bundle *bundles, char const *s, int i, int j);
t_bundle	*split_bundle(char const *str);
char		**dup_env(char **envp);

char		*ft_strndup(const char *s, int start);
int			is_space_str(char *str);
int			is_quote(char str, int preval);
int			check_priority(const char *str, int start);
int			check_vaild_str(char *str, int start);
int			is_vaild_char(char c);
int			ft_isallblank(char *str);
char		*join_env_str(char *content, char *env, int start);
char		*ft_strnstr_reverse(char *check_in_file, t_list *checks_dup);

int			is_redir_token(t_token *token);
int			is_io_token(t_token *token);
void		check_env_token(t_token *token);
void		replace_env_token(t_bundle *bundle, t_token *temp);

#endif
