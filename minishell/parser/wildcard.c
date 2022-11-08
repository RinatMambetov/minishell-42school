/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:09:29 by cluco            #+#    #+#             */
/*   Updated: 2022/03/28 22:56:24 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *get_tmpfile(void)
{
	int fd;
	pid_t pid;
	char *ex[2];

	fd = open("tmp_for_wildcard", O_CREAT | O_TRUNC | O_RDWR, 0664);
	if (fd < 0)
		exit(ft_putstr_fd("Error with tmp file for wild\n", 1));
	pid = fork();
	if (pid < 0)
		exit(ft_putstr_fd("Error with tmp fork for wild\n", 1));
	else if (pid == 0)
	{
		dup2(fd, 1);
		close(fd);
		ex[0] = "ls";
		ex[1] = NULL;
		execve("/usr/bin/ls", ex, NULL);
		ft_putstr_fd("execve crushed\n", 1);
	}
	else
		wait(NULL);
	return ("tmp_for_wildcard");
}

static char *find_in_ls(char *start, char *end)
{
	char *tmp[3];
	int i[2];

	i[0] = open(get_tmpfile(), O_RDWR);
	tmp[1] = ft_calloc(1, sizeof(char));
	i[1] = 1;
	while (i[1] > 0)
	{
		i[1] = get_next_line(&tmp[0], i[0]);
		if ((ft_strncmp(tmp[0], start, ft_strlen(start)) == 0 || ft_strlen(start) == 0) && (ft_strlen(end) == 0 || ft_strlen(tmp[0]) >= ft_strlen(start) + ft_strlen(end)) && (ft_strncmp(&tmp[0][ft_strlen(tmp[0]) - ft_strlen(end)], end, ft_strlen(end)) == 0))
		{
			tmp[2] = tmp[1];
			tmp[1] = ft_strjoin(tmp[2], tmp[0]);
			free(tmp[2]);
			tmp[2] = tmp[1];
			tmp[1] = ft_strjoin(tmp[2], " ");
			free(tmp[2]);
			free(tmp[0]);
		}
	}
	return (tmp[1]);
}

static char *replace_it(char *s, int *j)
{
	int i;
	int k;
	char *nl;
	char *start;
	char *end;

	i = j[0];
	while (i > 0 && (s[i] != ' '))
		i--;
	k = j[0] - i;
	start = ft_substr(s, j[0] - k + 1, k - 1);
	i = j[0];
	while (s[i] != ' ')
		i++;
	k = i - j[0];
	end = ft_substr(s, j[0] + 1, k - 1);
	nl = find_in_ls(start, end);
	unlink("tmp_for_wildcard");
	free(start);
	free(end);
	j[0] = i;
	return (nl);
}

static char *concat_to_nl(char *s, int *i, char *nl)
{
	char *tmp;
	char *tmp2;

	if (s[i[0]] == '*')
	{
		i[2] = i[0];
		while (s[i[2]] != ' ' && i[2] != 0)
			i[2]--;
		tmp = nl;
		nl = ft_strjoin(tmp, ft_substr(s, i[1], i[2] - i[1] + 1));
		free(tmp);
		tmp = replace_it(s, i);
		tmp2 = nl;
		nl = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	else
	{
		tmp = nl;
		nl = ft_strjoin(tmp, ft_substr(s, i[1], i[0] - i[1]));
		free(tmp);
	}
	return (nl);
}

char *wildcard(char *s)
{
	int i[3];
	char *nl;

	nl = ft_strdup("");
	i[0] = 0;
	while (s[i[0]])
	{
		i[1] = i[0];
		while (s[i[0]] != '*' && s[i[0]] != 0)
		{
			if (s[i[0]] == 34 && ft_strchr(&s[++i[0]], 34) != NULL)
				while (s[i[0]++] != 34)
					;
			else if (s[i[0]] == 39 && ft_strchr(&s[++i[0]], 39) != NULL)
				while (s[i[0]++] != 39)
					;
			else
				i[0]++;
		}
		nl = concat_to_nl(s, i, nl);
	}
	free(s);
	return (nl);
}
