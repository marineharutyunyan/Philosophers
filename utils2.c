/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:19:11 by maharuty          #+#    #+#             */
/*   Updated: 2023/01/07 14:05:48 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutexes(t_general_data *g_data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&g_data->print_mutex, 0);
	while (i < g_data->philos_count)
		pthread_mutex_init(&forks[i++], 0);
	return (-1);
}

void	set_philo_name(t_data *philo_data, int i)
{
	philo_data->name = i + 1;
}

void	life_cycle(t_data	*p_data)
{
	while (1)
	{
		pthread_mutex_lock(p_data->left_mutex);
		if (print_aciton(p_data, "has taken a fork"))
			break ;
		pthread_mutex_lock(p_data->right_mutex);
		if (print_aciton(p_data, "has taken a fork"))
			break ;
		if (print_aciton(p_data, "is eating 🍝"))
			break ;
		my_usleep(p_data->time_to_eat);
		p_data->last_eating_time = get_time(0);
		p_data->eating_count += 1;
		if (p_data->general_data->must_eat_count == p_data->eating_count)
			p_data->is_full = 1;
		pthread_mutex_unlock(p_data->left_mutex);
		pthread_mutex_unlock(p_data->right_mutex);
		if (print_aciton(p_data, "is sleeping"))
			break ;
		my_usleep(p_data->time_to_sleep);
		if (print_aciton(p_data, "is thinking"))
			break ;
	}
}	

void	*philo(void *arg)
{
	t_data	*p_data;

	p_data = (t_data *)arg;
	if (p_data->name % 2 == 0)
		usleep(1000);
	life_cycle(p_data);
	return (0);
}

void	create_philos(t_general_data *general_data, t_data *philos_data)
{
	int	i;

	i = 0;
	general_data->program_time = get_time(0);
	while (i < general_data->philos_count)
	{
		pthread_create(&philos_data[i].thread_id, NULL, philo, &philos_data[i]);
		i++;
	}
}
