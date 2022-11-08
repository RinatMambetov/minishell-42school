/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:22:36 by cluco             #+#    #+#             */
/*   Updated: 2022/04/16 20:50:56 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BOLD "\033[1m"
# define CLOSE "\033[0m"
# define PATH_LENGTH 512

typedef struct s_cmd
{
	char	**cmd;
	char	*type;
	char	*path;
	int		count;
	char	**e;
	int		fd1[2];
	int		fd2[2];
	int		*std_fd;
}	t_cmd;

int			g_exit_status;

void		set_std_fd(t_cmd *c);
int			*save_std(t_cmd *c);
char		**parse_execute(char *command, char **env);
void		launcher(t_cmd *c);
void		*free_all(t_cmd *c, char *s, char *message);
char		**redirects_cut_off(char *s, t_cmd *c);
void		run_execve(t_cmd *c, char **ex);
void		run_cmd(t_cmd *c, int i);
void		check_extra_arrows(t_cmd *c, char ch);
void		heredoc(char *s, int *i, t_cmd *c);
int			input(char *s, int *j, t_cmd *c);
void		durakskii_redirect(char *s, int *j, t_cmd *c);
char		*durakskaya_kavichka(char *s, int *j);
char		*dvoynaia_kavichka(char *s, int *j, char **env);
char		*dollar(char *s, int *j, char **env);
char		*simple_text(char *s, int *j);
int			output(char *s, int *j, t_cmd *c);
char		*get_arg(char *s, int *k);
int			rotate_quotes_and_text(char *s, int i);
char		*wildcard(char *s);
int			get_next_line(char **line, int fd);
char		*replace_var(char *s, char **env);
void		*xmalloc(size_t size);
void		ft_run_signals(int sig, t_cmd *c);
int			ft_get_fd(char *s, int *k);
int			check_digit(char *s, int i);
void		ft_check_exit_status(int exit_status);

void		ft_export(char **args, t_cmd *c);
void		ft_unset(char **args, t_cmd *c);
void		ft_env(char **args, t_cmd *c);
void		ft_cd(char **args, t_cmd *c);
void		ft_pwd(void);
void		ft_echo(char **args);
void		ft_exit(char **args);

int			ft_isbuiltin(char **args);
void		ft_run_builtin(char **args, t_cmd *c);
void		ft_free_arr(char **arr);
void		ft_sort_env(char **env, t_cmd *c);
int			ft_arrlen(char **arr);
int			ft_check_export_arg(char *arg);
int			ft_go_start(char *path, int root, char *start_path);
int			ft_cd_path(char *path, t_cmd *c);
char		*ft_get_name(char *arg);
int			ft_check_home_path(char *home_path);
char		*ft_get_home(char **env);
int			ft_check_oldpwd(char *oldpwd_path);
char		*ft_get_oldpwd(char **env);
void		ft_check_slash(char ch, int *i, int *root);
void		ft_export_start_path(t_cmd *c, char *start_path);
char		*ft_strjoin2(char *name, char *value);
char		**ft_add_env(char *name, char *arg, char **env);
char		**ft_strdup2(char **arr);
char		**ft_strdup2_add(char **arr, char *elem);
void		ft_ctrl_d(void);

extern void	rl_replace_line(const char *text, int clear_undo);

#endif
