/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:00:48 by crebelo-          #+#    #+#             */
/*   Updated: 2024/01/15 14:00:48 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

void	ft_putstr(char *str, size_t *len)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		(*len)++;
		i++;
	}
}

void	ft_putnbr(long long int nb, size_t *len)
{
	if (nb < 0)
	{
		(*len)++;
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10, len);
	(*len)++;
	nb = nb % 10 + '0';
	write(1, &nb, 1);
}

void	ft_putdec(long long int nb, size_t *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb < 0)
	{
		(*len)++;
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 16)
		ft_putdec(nb / 16, len);
	(*len)++;
	write(1, &base[nb % 16], 1);
}

int	ft_printf(const char *format, ... )
{
	int		i;
	va_list	args;
	size_t	len;

	i = 0;
	if (!format)
		return (0);
	va_start(args, format);
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				ft_putstr(va_arg(args, char *), &len);
			else if (format[i] == 'd')
				ft_putnbr((long long int)va_arg(args, int), &len);
			else if (format[i] == 'x')
				ft_putdec(va_arg(args, unsigned int), &len);
		}
		else
		{	
			len++;
			write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (len);
}

// int	main()
// {
// 	ft_printf("%s\n", "toto");
// 	ft_printf("\n");
// 	ft_printf("Magic %s is %d", "number", -2147483649);
// 	ft_printf("\n");
// 	ft_printf("Hexadecimal for %d is %x\n", 886, 886);
// }