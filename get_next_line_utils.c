/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:51:28 by julessainth       #+#    #+#             */
/*   Updated: 2024/05/24 15:59:33 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}*/

char	*ft_strjoinn(char *s1, char *s2)
{
	size_t	sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[sizetotal] = 0;
	return (res);
}
/*
char	*ft_strchr(const char *string, int searchedChar )
{
	char	*str;

	str = (char *)string;
	while (*str != searchedChar && *str != 0)
		str++;
	if (*str == searchedChar)
		return (str);
	else
		return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*c_alloc;
	size_t	i;

	if (size > 2147483647 || count > 2147483647)
		return (NULL);
	if (size == 0 || count == 0)
	{
		c_alloc = (void *)(malloc (1));
		*(unsigned char *)(c_alloc) = 0;
		return (c_alloc);
	}
	c_alloc = (void *)(malloc(count * size));
	if (!c_alloc)
		return (NULL);
	i = 0;
	while (i < (size * count))
	{
		*(unsigned char *)(c_alloc + i) = 0;
		i++;
	}
	return (c_alloc);
}
*/