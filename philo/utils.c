/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 21:01:07 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/09 11:21:23 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		++len;
	return (len);
}

static t_bool	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static char	*ft_strchr(const char *s, int c)
{
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	return (NULL);
}

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				neg;
	unsigned long	off;
	int				lim;

	res = 0;
	neg = 0;
	while (ft_strchr("\f\n\r\t\v ", *str) != NULL)
		++str;
	if (ft_strchr("+-", *str) != NULL)
	{
		if (*str == '-')
			neg = 1;
		++str;
	}
	off = (unsigned long)LONG_MAX + neg;
	lim = off % 10;
	off /= 10;
	while (ft_isdigit(*str) && (res < off || (res == off && *str - '0' <= lim)))
		res = res * 10 + *(str++) - '0';
	if (ft_isdigit(*str))
		return (neg - 1);
	if (neg)
		res = -res;
	return ((int)res);
}

int	print_error(const char *s)
{
	const size_t	len = ft_strlen(s);

	write(STDERR, s, len);
	return (1);
}
