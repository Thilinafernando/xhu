/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:13:13 by xhamzall          #+#    #+#             */
/*   Updated: 2025/01/17 00:08:46 by xhamzall         ###   ########.fr       */
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
	char *buffer;
	ssize_t	nbr_read;
	char *temp;

	temp = 0;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return (NULL);
	while (1)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		nbr_read = read(fd, buffer, BUFFER_SIZE);
		if (nbr_read == -1)
			return (free(buffer), free(str),NULL);
		if (nbr_read == 0)
			break;
		buffer[nbr_read] = '\0';
		if(str)
			temp = ft_strjoin(str, buffer);
		else
			temp = ft_strdup(buffer);
		free(str);
		str = temp;
		if (ft_strchr(str, '\n'))
			break;
	}
	return (free(buffer),str);
}
static char	*make_ln(char *str)
{
	size_t	i;
	size_t	new_ln;
	char	*mk_line;

	if(!str)
		return (NULL);
	i = 0;
	new_ln = 0;
	while (str[i] && str[i] != '\n' )
		i++;
	if (str[i] == '\n')
		new_ln++;
	mk_line = malloc(((new_ln + i) + 1)* sizeof(char));
	if (!mk_line)
		return (NULL);
	ft_memcpy(mk_line, str, (i + new_ln));
	mk_line[i + new_ln] = '\0';
	return (mk_line);
}
static char	*prev (char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	// if(!str || str[i] == '\0')
	// 	return (NULL);
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n' )
		i++;
	if (str[i] == '\0')
		return(free(str), str = NULL, NULL);
	tmp = ft_strdup(&str[i+1]);
	if (!tmp)//
		return(free(str), str = NULL, NULL);
	free (str);
	str = NULL;
	return(tmp);
}

char	*get_next_line(int fd)
{
	static char *str;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_ln(fd, str);
	if (!str)
		return (NULL);
	line = make_ln(str);
	if(!line || line[0] == '\0')
		return(NULL);
	str = prev(str);
	return (line);
}
int	main(void)
{
	int	fd;
	char *line;

	fd = open("txt.txt", O_RDWR);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// close(fd);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	get_next_line(fd);
	return (0);
}

