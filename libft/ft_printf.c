/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:59:11 by jou               #+#    #+#             */
/*   Updated: 2024/01/14 20:07:19 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putptr(unsigned long arg, int base, char *set)
{
	char	str[16];
	int	count;
	int	i;

	i = -1;
	count = 0;
	if (arg == 0)
		return (write(1, "(nil)", 5));
	else
	{
		while (arg != 0)
		{
			str[++i] = set[arg % base];
			arg /= base;
		}
		count += write (1, "0x", 2);
		while (i >= 0)
			count += write (1, &str[i--], 1);
	}
	return (count);
}

static int	ft_putnbr(long arg, int base, char *set,  int u)
{
	int	sig;
	char	str[16];
	unsigned int	nb;
	int	i;

	i = -1;
	sig = 0;
	if (arg == 0)
		return (write(1, "0", 1));
	if (arg < 0 && !u)
	{
		arg *= -1;
        	sig++;
	}
	nb = arg;
	while (nb != 0)
	{
		str[++i] = set[nb % base];
		nb /= base;
	}
	if (sig && !u)
		str[++i] = '-';
	while (i >= 0)
		nb += write (1, &str[i--], 1);
	return (nb);
}

static int	ft_putstr(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (write(1, "(null)", 6));
	else
		while (arg[i])
		{
			write(1, &arg[i], 1);
			i++;
		}
	return (i);
}

static int	ft_checkspec(va_list args, char spec)
{
	int	count;
	char	c;

	count = 0;
	if (spec == 'c')
	{
		c = va_arg(args, int);
		count = write(1, &c, 1);
	}
	else if (spec == 'i' || spec == 'd')
		count = ft_putnbr(va_arg(args, int), 10, "0123456789", 0);
	else if (spec == 'u')
		count = ft_putnbr(va_arg(args, unsigned int), 10, "0123456789", 1);
	else if (spec == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (spec == 'p')
		count = ft_putptr(va_arg(args, unsigned long), 16, "0123456789abcdef");
	else if (spec == 'x' || spec == 'p')
		count = ft_putnbr(va_arg(args, int), 16, "0123456789abcdef", 1);
	else if (spec == 'X')
		count = ft_putnbr(va_arg(args, int), 16, "0123456789ABCDEF", 1);
	else if (spec == '%')
		count = write(1, "%", 1);
	return (count);
}
  
int	ft_printf(const char *str, ...)
{
	int	i;
	int	count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	while(str[i])
	{
		if (str[i] == '%')
			count += ft_checkspec(args, str[++i]);
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
