#include "philosophers.h"

pthread_mutex_t	mutex;

int	init_args(int argc, char **argv, t_general_data *g_data,
		t_data *philo_data, int i)
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
	philo_data->name = i + 1;
	return (1);
}

#include <errno.h>

int	print_aciton(t_data *philo_data, char *str)
{
	// printf("the mutex pointer is ----------- %p\n", &philo_data->general_data->print_mutex);
	if (pthread_mutex_lock(&philo_data->general_data->print_mutex) != 0)
	{
		// printf("errno = %d\n", errno);
		// printf("code = %d\n", EDEADLK);
		perror("lock");
		return(1);
	}
	// pthread_mutex_lock(&mutex);
	if (!is_equal(str, "full"))
	{
		printf(" %lld %d %s\n", get_time(philo_data->general_data->program_time), philo_data->name, str);
		if (!is_equal(str, "died"))
			if(pthread_mutex_unlock(&philo_data->general_data->print_mutex) != 0 )
			{
				perror("un lock");
				return(1);
			}
			// pthread_mutex_unlock(&mutex);
	}
	return (0);
}


void	*philo(void *arg)
{
	t_data	*p_data;

	p_data = (t_data *)arg;
	if (p_data->name % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(p_data->left_mutex);
		if (print_aciton(p_data, "has taken a fork"))
			return(0);
		pthread_mutex_lock(p_data->right_mutex);
		if (print_aciton(p_data, "has taken a fork"))
			return (0);
		print_aciton(p_data, "is eating");
		my_usleep(p_data->time_to_eat);
		p_data->last_eating_time = get_time(0);
		p_data->eating_count += 1;
		if (p_data->general_data->must_eat_count == p_data->eating_count)
			p_data->is_full = 1;
		pthread_mutex_unlock(p_data->left_mutex);
		pthread_mutex_unlock(p_data->right_mutex);
		if (print_aciton(p_data, "is sleeping"))
			return (0);
		my_usleep(p_data->time_to_sleep);
		if (print_aciton(p_data, "is thinking"))
			return (0);
	}
	return (0);
}

int	is_dead (t_data	*philos_data, pthread_mutex_t *forks)
{
	int			i;
	int			all_are_full;
	long long	program_time;

	i = 0;
	all_are_full = 0;
	// program_time = get_time(0);
	while (1)
	{
		if (philos_data[i].is_full)
			all_are_full += 1;
		// program_time = get_time(0) - philos_data[i].last_eating_time;
		program_time = get_time(0);
		if (program_time >  philos_data[i].last_eating_time + philos_data->time_to_die)
			break;
		if (i == philos_data->general_data->philos_count - 1)
		{
			i = -1;
			if (all_are_full == philos_data->general_data->philos_count)
			{
				printf("all_are_full %d ,,, philos_count %d\n", all_are_full, philos_data->general_data->philos_count);
				print_aciton(philos_data + 1, "full");
				return (1);
			}
			all_are_full = 0;
		}
		i++;
	}
	print_aciton(philos_data + i, "died");
	// pthread_mutex_destroy(&philos_data->general_data->print_mutex);
	// i = 0;
	// while (i < philos_data->general_data->philos_count)
	// {
	// 	pthread_mutex_destroy(&forks[i++]);
	// }
	return (1);
}

void	create_mutexes(t_general_data *g_data, int i, pthread_mutex_t *forks)
{
	pthread_mutex_init(&g_data->print_mutex, 0);
	while (i < g_data->philos_count)
		pthread_mutex_init(&forks[i++], 0);
}

void set_mutexes(t_data *philo_data, t_general_data *g_data, pthread_mutex_t *forks, int i)
{
	philo_data->left_mutex = &forks[i];
	if (i == g_data->philos_count - 1)
		philo_data->right_mutex = &forks[0];
	else
		philo_data->right_mutex = &forks[i + 1];
}

void create_philos(t_general_data *general_data, t_data *philos_data)
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

int arg_check(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (arg_validity_check(argc, argv))
			return (1);
	}
	return (0);
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
		i = 0;
		philos_data = malloc(sizeof(t_data) * general_data.philos_count);
		forks = malloc(sizeof(pthread_mutex_t) * general_data.philos_count);
		create_mutexes(&general_data, i, forks);
		i = 0;
		while (i < general_data.philos_count)
		{
			init_args(argc, argv, &general_data, &philos_data[i], i);
			set_mutexes(&philos_data[i], &general_data, forks, i);
			i++;
		}
		create_philos(&general_data, philos_data);
		i = 0;
		while (pthread_detach(philos_data[i].thread_id))
			i++;
		is_dead(philos_data, forks);
		printf("game_over\n");
	}
	// sleep(1);
	return (write(1 ,"+", 1));
}
