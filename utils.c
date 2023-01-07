/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:19:08 by maharuty          #+#    #+#             */
/*   Updated: 2023/01/07 13:19:09 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_args(int argc, char **argv, t_general_data *g_data,
		t_data *philo_data)
{
	philo_data->general_data = g_data;
	philo_data->is_full = 0;
	philo_data->eating_count = 0;
	if (argc == 6)
		philo_data->general_data->must_eat_count = ft_atoi(argv[5]);
	else
		philo_data->general_data->must_eat_count = 0;
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	philo_data->last_eating_time = get_time(0);
	return (1);
}

int	is_equal(char *s1, char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;

	i = 0;
	s1_len = ft_str_len(s1);
	s2_len = ft_str_len(s2);
	if (s1_len == s2_len)
	{
		while (s1[i])
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

long	long	get_time(long long last_eating_time)
{
	struct timeval	current_time;
	long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	if (last_eating_time != 0)
		return (time - last_eating_time);
	return (time);
}

void	my_usleep(int requested_time)
{
	long long	time;

	time = get_time(0);
	while (get_time(0) - time < requested_time)
		usleep(500);
}

int	arg_validity_check(int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 1;
	while (i <= argc - 1)
	{
		j = 0;
		while (j < ft_strlen(argv[i]))
		{
			if (ft_isdigit(argv[i][j]))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
