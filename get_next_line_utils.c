/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:15:09 by xhamzall          #+#    #+#             */
/*   Updated: 2025/01/16 17:13:34 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1 = s1 ? strlen(s1) : 0;
	size_t	len2 = s2 ? strlen(s2) : 0;
	char	*result = malloc(len1 + len2 + 1);

	if (!result)
		return (NULL);

	if (s1)
		memcpy(result, s1, len1);
	if (s2)
		memcpy(result + len1, s2, len2);

	result[len1 + len2] = '\0';
	free(s1); // Free the old string if necessary
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
char	*ft_strdup(const char *s)
{
	size_t	len = s ? strlen(s) : 0;
	char	*dup = malloc(len + 1);

	if (!dup)
		return (NULL);

	memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*input;
	size_t	result;
	size_t	i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	result = nmemb * size;
	if (result / nmemb != size)
		return (NULL);
	input = malloc(nmemb * size);
	if (input == NULL)
		return (NULL);

	while (i < result)
	{
			input[i++] = '\0';
	}
	return (input);
}
