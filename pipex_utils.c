/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:20:19 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 03:22:26 by eniddealla       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*s;
	char	*dp;
	int		i;

	s = (char *)s1;
	if ((dp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))) == 0)
		return (0);
	if (!s)
	{
		*dp = '\0';
		return (dp);
	}
	i = 0;
	while (*s)
	{
		dp[i] = *s;
		s++;
		i++;
	}
	dp[i] = '\0';
	return (dp);
}

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned	char	*ss1;
	unsigned	char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		if (!*ss1)
			return (0);
		ss1++;
		ss2++;
	}
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ss;

	ss = (char *)s;
	i = ft_strlen(ss);
	while (i >= 0)
	{
		if (ss[i] == (char)c)
			return (&ss[i]);
		i--;
	}
	return (0);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
	char	*ss1;
	char	*ss2;
	char	*join;
	int		i;

	ss1 = (char *)s1;
	ss2 = (char *)s2;
	if (ss1 && ss2)
	{
		if ((join = (char *)malloc(sizeof(char) *
						(ft_strlen(ss1) + ft_strlen(ss2) + 1))) == 0)
			return (0);
		i = 0;
		while (*ss1)
			join[i++] = *ss1++;
		while (*ss2)
			join[i++] = *ss2++;
		join[i] = '\0';
		return (join);
	}
	return (0);
}

void    error_handler(char *str)
{
    write(1, "Error:", 7);
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
    exit(2);
}