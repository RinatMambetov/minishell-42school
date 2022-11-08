/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:11:57 by cluco             #+#    #+#             */
/*   Updated: 2022/04/18 11:56:35 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static char **init_env(char **env)
{
	int i;
	char **e;

	i = 0;
	while (env[i])
		i++;
	e = xmalloc(sizeof(char *) * ++i);
	i = -1;
	while (env[++i])
		e[i] = ft_strdup(env[i]);
	e[i] = NULL;
	return (e);
}

static int only_tabs_etc(char *s)
{
	int i;

	if (s[0] == '|')
	{
		ft_putstr_fd("minishell: Syntax error ", 2);
		return (ft_putstr_fd("near unexpected token \"|\"\n", 2));
	}
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == 10 || s[i] == 32 || s[i] == 11)
			i++;
		else
			return (0);
	}
	return (1);
}

static void ft_use_line(char *line, char ***e)
{
	char *wild;
	char *nl;

	add_history(line);
	wild = wildcard(line);
	nl = replace_var(wild, *e);
	free(wild);
	*e = parse_execute(nl, *e);
	free(nl);
}

int main(int argc, char **argv, char **env)
{
	char *line;
	char **e;

	(void)argv;
	g_exit_status = EXIT_SUCCESS;
	ft_run_signals(1, NULL);
	e = init_env(env);
	while (argc >= 0)
	{
		line = readline("\033[0;36m" BOLD "minishell🐚 " CLOSE);
		if (!line)
			ft_ctrl_d();
		if (ft_strlen(line) > 0 && only_tabs_etc(line) == 0)
			ft_use_line(line, &e);
		else
			free(line);
	}
	return (0);
}
