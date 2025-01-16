/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:13:13 by xhamzall          #+#    #+#             */
/*   Updated: 2025/01/16 17:38:35 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*str_src;
	unsigned char		*str_dest;
	size_t				i;

	i = 0;
	str_dest = dest;
	str_src = src;
	if (dest == NULL && src == NULL && n > 0)
		return (NULL);
	while (i < n)
	{
		str_dest[i] = str_src[i];
		i++;
	}
	return (dest);
}

static char	*read_ln(int fd, char *str)
{
	char	*buffer;
	char	*temp = NULL;
	ssize_t	nbr_read;

	buffer = calloc(BUFFER_SIZE + 1, 1);
	while (1)
	{
		nbr_read = read(fd, buffer, BUFFER_SIZE);
		if (nbr_read == -1)
			return (free(buffer), free(str), NULL);
		if (nbr_read == 0)
			break;
		buffer[nbr_read] = '\0';
		temp = ft_strjoin(str, buffer);
		if (!temp)
            return (free(buffer), free(str), NULL);
		str = temp;
		if (ft_strchr(str, '\n'))
			break;
	}

	free(buffer);
	return (str);
}

static char	*make_ln(char *str)
{
	size_t	i = 0;
	char	*mk_line;

	if (!str)
		return (NULL);

	while (str[i] && str[i] != '\n')
		i++;

	mk_line = malloc(i + (str[i] == '\n') + 1);
	if (!mk_line)
		return (NULL);

	memcpy(mk_line, str, i + (str[i] == '\n'));
	mk_line[i + (str[i] == '\n')] = '\0';

	return (mk_line);
}

static char	*prev(char *str)
{
	size_t	i = 0;
	char	*tmp;

 	if (!str)
        return (NULL);
	while (str[i] && str[i] != '\n')
		i++;

	if (str[i] =='\0')
		return (free(str), NULL);

	tmp = ft_strdup(&str[i + 1]);
	if (!tmp)
        return (free(str), NULL);
	return (free(str), tmp);
}

char	*get_next_line(int fd)
{
    static char	*str;
    char		*line;

    str = read_ln(fd, str);
    if (!str)
        return (NULL);

    line = make_ln(str);
    if (!line || line[0] == '\0')
        return (free(str), free(line), NULL);

    str = prev(str);
    return (line);
}

/*   int	main(void)
{
	int	fd;
	char *line;

	fd = open("text.txt", O_RDWR);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */
 int main()
{
	int	fd = open("text.txt", O_RDWR);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
/*
int main()
{
	//int	fd = open("text.txt", O_RDWR);
	char *line;

	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	free(line);
	//close(fd);
	return (0);
} */

