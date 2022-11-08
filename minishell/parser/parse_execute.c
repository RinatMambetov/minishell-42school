/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 00:02:18 by cluco            #+#    #+#             */
/*   Updated: 2022/04/07 20:31:02 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int check_quotes(char *s, int i, int n[3])
{
	if (s[i] == 34 && ft_strchr(&s[++i], 34) != NULL)
	{
		while (s[i] != 34 && s[i] != 0)
			i++;
		if (s[i] != 0)
			n[1]++;
	}
	if (s[i] == 39 && ft_strchr(&s[++i], 39) != NULL)
	{
		while (s[i] != 34 && s[i] != 0)
			i++;
		if (s[i] != 0)
			n[2]++;
	}
	return (i);
}

static int cmd_count(char *s)
{
	int n[3];
	int i;

	n[0] = 1;
	n[1] = 0;
	n[2] = 0;
	i = 0;
	while (s[i])
	{
		i = check_quotes(s, i, n);
		if (s[i] == '|')
		{
			n[0]++;
			if (s[i + 1] == '|')
				i++;
		}
		if (s[i] == '&' && s[i + 1] == '&')
		{
			n[0]++;
			i++;
		}
		if (s[i] != 34 && s[i] != 39 && s[i] != 0)
			i++;
	}
	return (n[0]);
}

static void get_pipe_or(char *s, int i[2], t_cmd *c)
{
	if (s[i[0] + 1] == '|')
		c->type[c->count] = 'r';
	else
		c->type[c->count] = '|';
	while (s[i[1]] == ' ')
		i[1]++;
	c->cmd[c->count] = ft_substr(s, i[1], i[0] - i[1]);
	if (c->cmd[c->count] == NULL)
		free_all(c, "158940", strerror(errno));
	if (s[i[0] + 1] == '|')
		i[0]++;
	i[1] = i[0] + 1;
	c->count++;
}

static void get_next_cmd(char *s, int i[2], t_cmd *c)
{
	while (s[i[0]] != 34 && s[i[0]] != 39 && s[i[0]] != '|' && !(s[i[0]] == '&' && s[i[0] + 1] == '&') && s[i[0]] != 0)
		i[0]++;
	if (s[i[0]] == 34 && ft_strchr(&s[++i[0]], 34) != NULL)
		while (s[i[0]] != 34 && s[i[0]] != 0)
			i[0]++;
	if (s[i[0]] == 39 && ft_strchr(&s[++i[0]], 39) != NULL)
		while (s[i[0]] != 39 && s[i[0]] != 0)
			i[0]++;
	if (s[i[0]] == '|')
		get_pipe_or(s, i, c);
	if (s[i[0]] == '&' && s[i[0] + 1] == '&')
	{
		c->type[c->count] = '&';
		while (s[i[1]] == ' ')
			i[1]++;
		c->cmd[c->count] = ft_substr(s, i[1], i[0] - i[1]);
		if (c->cmd[c->count] == NULL)
			free_all(c, "158940", strerror(errno));
		i[0]++;
		i[1] = i[0] + 1;
		c->count++;
	}
}

char **parse_execute(char *command, char **env)
{
	t_cmd *c;
	int i[2];
	char **e;

	c = xmalloc(sizeof(t_cmd));
	c->std_fd = save_std(c);
	c->e = env;
	c->count = cmd_count(command);
	c->cmd = xmalloc(sizeof(char *) * (c->count + 1));
	c->type = xmalloc(sizeof(char) * (c->count + 1));
	i[0] = -1;
	i[1] = 0;
	c->count = 0;
	while (command[++i[0]])
		get_next_cmd(command, i, c);
	while (command[i[1]] == ' ')
		i[1]++;
	c->cmd[c->count] = ft_substr(command, i[1], i[0] - i[1]);
	if (c->cmd[c->count] == NULL)
		free_all(c, "158940", strerror(errno));
	c->cmd[++c->count] = NULL;
	launcher(c);
	e = c->e;
	free_all(c, "184", NULL);
	return (e);
}
