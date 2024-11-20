/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:06:48 by akar              #+#    #+#             */
/*   Updated: 2024/11/20 17:06:51 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_line1(int fd, char *buffer, char *stack)
{
	int		read_byte;
	char	*temp;

	while (1)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (0);
		else if (read_byte == 0)
			break ;
		buffer[read_byte] = '\0';
		if (!stack)
			stack = ft_strdup("");
		temp = stack;
		stack = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stack);
}

char	*clean_stack1(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (str == NULL)
		return (NULL);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stack[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_line1(fd, buffer, stack[fd]);
	free(buffer);
	if (line == NULL)
	{
		stack[fd] = NULL;
		return (NULL);
	}
	stack[fd] = clean_stack1(line);
	return (line);
}
