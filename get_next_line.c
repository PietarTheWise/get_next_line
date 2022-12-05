/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:57:02 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/20 13:04:32 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*string_joiner(char **str, char *buffer, int flag);

static int	ft_has_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	if (str[0] == '\n')
		return (0);
	return (-1);
}

static int	ft_last_string(char **tmp, char **line)
{
	int		i;
	char	*o_temp;

	i = ft_has_newline(*tmp);
	if (i < 0)
	{
		*line = ft_strsub(*tmp, 0, ft_strlen(*tmp));
		free(*tmp);
		*tmp = NULL;
		if ((*line)[0])
			return (1);
		return (0);
	}
	else
	{
		*line = ft_strsub(*tmp, 0, (size_t)i);
		o_temp = ft_strsub(*tmp, i + 1, ft_strlen(*tmp + i + 1));
		free(*tmp);
		*tmp = NULL;
		*tmp = o_temp;
		return (1);
	}
}

static int	ft_return(int reader, char **line, char **tmp)
{
	int		i;
	int		last;

	i = 0;
	i = ft_has_newline(*tmp);
	if (reader == -1)
		return (-1);
	if (!reader)
	{
		last = ft_last_string(tmp, line);
		if (!line)
		{
			return (-1);
		}
		return (last);
	}
	if (i >= 0)
	{
		*line = ft_strsub(*tmp, 0, (size_t)i);
		string_joiner(tmp, "", i);
		if (!(*line))
			return (-1);
		return (1);
	}
	return (2);
}

static char	*string_joiner(char **str, char *buffer, int flag)
{
	char	*o_temp;
	char	*tmp;

	if (flag < 0)
	{
		tmp = ft_strjoin(*str, buffer);
		free(*(str));
		*str = NULL;
		return (tmp);
	}
	else
	{
		o_temp = ft_strsub(*str, flag + 1, ft_strlen(*str + flag + 1));
		free(*str);
		*str = NULL;
		*str = o_temp;
		return (*str);
	}
}

int	get_next_line(const int fd, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	static char		*tmp[10240];
	int				reader;
	int				ret_val;

	if (fd < 0 || fd > 10240 || BUFF_SIZE <= 0 || fd == 1 || line == NULL)
		return (-1);
	if (!tmp[fd])
		tmp[fd] = ft_strnew(0);
	while (1 && tmp[fd])
	{
		ft_bzero(buffer, BUFF_SIZE + 1);
		reader = read(fd, buffer, BUFF_SIZE);
		tmp[fd] = string_joiner(&(tmp[fd]), buffer, -1);
		ret_val = ft_return(reader, line, &(tmp[fd]));
		if (!ret_val)
			return (0);
		if (ret_val == 1)
			return (1);
		if (ret_val == -1 || !tmp[fd] || reader == -1)
			return (-1);
	}
	return (-1);
}
