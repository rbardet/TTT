#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void	putstr(char *str, int *ret)
{
	int i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*ret) += 6;
		return ;
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		(*ret)++;
	}
}

void	putnbr(int nb, int *ret)
{
	char c;
	if (nb == -2147483648)
	{
		putstr("-2147483648", ret);
		return ;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		(*ret)++;
		nb *= -1;
	}
	if (nb > 9)
		putnbr(nb / 10, ret);
	c = (nb % 10) + '0';
	write(1, &c, 1);
	(*ret)++;
}

void	puthex(unsigned int nb, int *ret)
{
	char *base = "0123456789abcdef";
	if (nb >= 16)
		puthex(nb / 16, ret);
	write(1, &base[nb % 16], 1);
	(*ret)++;
}

int	ft_format(va_list arg, char c)
{
	int ret = 0;
	if (c == 's')
		putstr(va_arg(arg, char *), &ret);
	else if (c == 'x')
		puthex(va_arg(arg, unsigned int), &ret);
	else if (c == 'd')
		putnbr(va_arg(arg, int), &ret);
	return (ret);
}
int	ft_printf(const char *str, ...)
{
	va_list arg;
	int		i = 0;
	int		ret = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ret += ft_format(arg, str[i + 1]);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
			ret++;
		}
	}
	return (ret);
}
