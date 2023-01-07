/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:19:00 by maharuty          #+#    #+#             */
/*   Updated: 2023/01/07 14:09:14 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_aciton(t_data *p_data, char *str)
{
	if (pthread_mutex_lock(&p_data->general_data->print_mutex) != 0)
		return (1);
	if (!is_equal(str, "full"))
	{
		printf(" %lld %d %s\n", get_time(p_data->general_data->program_time),
			p_data->name, str);
		if (!is_equal(str, "died"))
		{
			if (pthread_mutex_unlock(&p_data->general_data->print_mutex) != 0)
				return (1);
		}
	}
	return (0);
}

void	set_mutes(t_data *p_data, t_general_data *g, pthread_mutex_t *f, int i)
{
	p_data->left_mutex = &f[i];
	if (i == g->philos_count - 1)
		p_data->right_mutex = &f[0];
	else
		p_data->right_mutex = &f[i + 1];
}

void	ft_loop(int	*i, int *all_are_full, t_data	*philos)
{
	if (*i == philos->general_data->philos_count - 1)
	{
		*i = -1;
		*all_are_full = 0;
	}
	(*i)++;
}

int	is_dead(t_data	*philos)
{
	int			i;
	int			all_are_full;
	long long	prog_time;

	i = 0;
	all_are_full = 0;
	while (1)
	{
		if (philos[i].is_full)
			all_are_full += 1;
		prog_time = get_time(0);
		if (prog_time > philos[i].last_eating_time + philos->time_to_die)
			break ;
		if (all_are_full == philos->general_data->philos_count)
		{
			print_aciton(philos + i, "full");
			return (1);
		}
		ft_loop(&i, &all_are_full, philos);
	}
	print_aciton(philos + i, "died");
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			*philos_data;
	pthread_mutex_t	*forks;
	t_general_data	general_data;
	int				i;

	if (arg_check(argc, argv))
	{
		general_data.philos_count = ft_atoi(argv[1]);
		if (general_data.philos_count <= 0 || general_data.philos_count > 200)
			return (1);
		philos_data = malloc(sizeof(t_data) * general_data.philos_count);
		forks = malloc(sizeof(pthread_mutex_t) * general_data.philos_count);
		if (!philos_data || !forks)
			return (1);
		i = create_mutexes(&general_data, forks);
		while (++i < general_data.philos_count)
		{
			init_args(argc, argv, &general_data, &philos_data[i]);
			set_philo_name(&philos_data[i], i);
			set_mutes(&philos_data[i], &general_data, forks, i);
		}
		create_philos(&general_data, philos_data);
		is_dead(philos_data);
	}
	return (0);
}
