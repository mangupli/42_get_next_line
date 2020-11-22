/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:38:06 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/22 16:38:08 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_line(char **stack, char **line)
{
	char *ptr_n;
	char *tmp_stack;

	ptr_n = ft_strchr(*stack, '\n');
	if (ptr_n)
	{
		*ptr_n = '\0';
		tmp_stack = *stack;
		*line = ft_strdup(tmp_stack);
		*stack = ft_strdup(++ptr_n);
		free(tmp_stack);
		return (1);
	}
	else
		return (0);
}

int		read_file(int fd, char **stack, char *buf, char **line)
{
	char	*tmp_stack;
	int		ret;
	int		new_line;

	new_line = 0;
	while (!new_line && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!*stack)
			*stack = ft_strdup("");
		tmp_stack = *stack;
		*stack = ft_strjoin(tmp_stack, buf);
		free(tmp_stack);
		if (find_line(stack, line))
			new_line = 1;
	}
	if (ret < 0)
		return (ret);
	return (ret > 0 ? 1 : ret);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*stack[256];

	if (!line || (fd < 0 || fd >= 256) || BUFFER_SIZE < 1 \
			|| !(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (stack[fd])
		if ((ret = find_line(&stack[fd], line)))
		{
			free(buf);
			return (1);
		}
	ret = read_file(fd, &stack[fd], buf, line);
	free(buf);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret)
			*line = ft_strdup("");
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (ret);
}
