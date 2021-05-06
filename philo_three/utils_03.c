/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:43:43 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:43:51 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nu;
	unsigned int	i;
	unsigned int	n_size;

	if (n >= 0)
		nu = (unsigned int)n;
	else
		nu = (unsigned int)(n * -1);
	n_size = int_size(nu);
	if (n < 0)
		n_size++;
	str = (char *)malloc(n_size + 1);
	if (n < 0)
		str[0] = '-';
	i = n_size - 1;
	while (nu > 9)
	{
		str[i--] = (char)(nu % 10 + 48);
		nu /= 10;
	}
	str[i] = (char)(nu % 10 + 48);
	str[n_size] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * \
	(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	p = str;
	if (s1)
	{
		while (*s1)
			*str++ = *s1++;
	}
	if (s2)
	{
		while (*s2)
			*str++ = *s2++;
	}
	*str = '\0';
	return (p);
}
