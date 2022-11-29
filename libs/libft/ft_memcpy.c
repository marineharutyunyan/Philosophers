/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:43:33 by maharuty          #+#    #+#             */
/*   Updated: 2022/04/03 20:22:03 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstc;
	const char	*srcc;

	if (!dst && !src)
		return (0);
	dstc = (char *)dst;
	srcc = (const char *)src;
	while (n--)
		dstc[n] = srcc[n];
	return (dst);
}
