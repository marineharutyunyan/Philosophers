/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:19:13 by maharuty          #+#    #+#             */
/*   Updated: 2023/01/07 13:19:14 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	arg_check(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (arg_validity_check(argc, argv))
			return (1);
	}
	return (0);
}
