/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:37:22 by Cluco             #+#    #+#             */
/*   Updated: 2022/04/16 20:49:59 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Error malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	get_next_line(char **line, int fd)
{
	int		rd;
	int		i;
	char	ch;
	char	*buffer;

	buffer = malloc(100000);
	*line = buffer;
	i = 0;
	rd = read(fd, &ch, 1);
	while (rd > 0 && ch != '\n')
	{
		buffer[i++] = ch;
		rd = read(fd, &ch, 1);
	}
	buffer[i] = '\0';
	return (rd);
}

static void	free_all2(char *s, int i, t_cmd *c)
{
	int	j;

	if (s[i] == '7')
		free(c->path);
	else if (s[i] == '8')
		free(c->type);
	else if (s[i] == '9')
	{
		free(c->std_fd);
		j = -1;
		while (c->e[++j] != NULL)
			free(c->e[j]);
		free(c->e);
	}
	else if (s[i] == '0')
	{
		unlink("clucoheredoc");
		exit(errno);
	}
}

void	*free_all(t_cmd *c, char *s, char *message)
{
	int	i;
	int	j;

	if (message != NULL && ft_strlen(message) > 10)
		ft_putstr_fd(message, 2);
	else if (message != NULL)
		perror(message);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '1')
		{
			j = c->count - 1;
			while (j >= 0)
				free(c->cmd[j--]);
			free(c->cmd);
		}
		else if (s[i] == '4')
			free(c);
		free_all2(s, i, c);
	}
	return (NULL);
}
