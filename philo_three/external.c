#include "philo_three.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

size_t	ft_strlen(const char *str)
{
	size_t	k;

	k = 0;
	if (str)
	{
		while (*str)
		{
			k++;
			str++;
		}
	}
	return (k);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	ft_isdigit(int ch)
{
	return (ch >= '0' && ch <= '9');
}

int	int_size(unsigned int a)
{
	int	n;

	n = 0;
	while (a > 9)
	{
		a /= 10;
		++n;
	}
	return (n + 1);
}
