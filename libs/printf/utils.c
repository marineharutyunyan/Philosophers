/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:40:39 by maharuty          #+#    #+#             */
/*   Updated: 2022/05/16 21:45:38 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	*print_unsigned_number(unsigned int n)
{
	static int	len;

	if (n == 0)
		len += print_char('0');
	else
	{
		if (n > 9)
			print_unsigned_number(n / 10);
		len += print_char(n % 10 + '0');
	}
	return (&len);
}

int	*print_hex(size_t num, char type)
{
	static int	len;
	char		*alpha;

	alpha = "0123456789abcdef";
	if (type == 'X')
		alpha = "0123456789ABCDEF";
	if (num > 15)
		print_hex(num / 16, type);
	len += print_char(alpha[num % 16]);
	return (&len);
}

int	print_pointer(uintptr_t ptr)
{
	int	len;
	int	*templen;

	write(1, "0x", 2);
	len = 2;
	templen = print_hex(ptr, 'x');
	len += *templen;
	*templen = 0;
	return (len);
}
