/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:36:22 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 14:37:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((dst != src))
	{
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	return ((char *)ft_memcpy(ptr, s1, len));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	len2;
	char	*ptr;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		else if (s2)
			return (ft_strdup(s2));
		else
			return (ft_strdup(""));
	}
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + len2 + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ft_memcpy(ptr + len, s2, len2);
	ptr[len + len2] = 0;
	return (ptr);
}

static void	fill(char *s, long int n, int count)
{
	int	flag;

	flag = 0;
	s[count--] = 0;
	if (n < 0)
	{
		n *= -1;
		s[0] = '-';
		flag = 1;
	}
	else if (n == 0)
		s[count] = '0';
	while (count >= flag)
	{
		s[count--] = n % 10 + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	long int	d;
	int			count;
	char		*ptr;

	d = n;
	count = 0;
	if (n < 0)
	{
		d *= -1;
		count++;
	}
	else if (n == 0)
		count++;
	while (d > 0)
	{
		d /= 10;
		count++;
	}
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	fill(ptr, n, count);
	return (ptr);
}
