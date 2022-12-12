#include "philosophers.h"

long long get_time(long long last_eating_time)
{
	struct timeval current_time;
    gettimeofday(&current_time, NULL);
	long long time = (current_time.tv_sec * 1000) + (current_time.tv_usec/1000);
	if (last_eating_time != 0)
		return(time - last_eating_time);
    return (time);
}

void my_usleep(int requested_time)
{
	long long time;
	
	time = get_time(0);
	while (get_time(0) - time < requested_time)
		usleep(500);
}

int	arg_validity_check(int argc, char **argv)
{
	int	i;
	size_t	j;

	i = 1;
	while (i == argc - 1)
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

int	init_args(int argc, char **argv, t_general_data *g_data, t_data *philo_data, int i)
{
	if (argc == 6)
		philo_data->eating_count = ft_atoi(argv[5]);
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	philo_data->last_eating_time = get_time(0);
	philo_data->name = i+1;
	philo_data->general_data = g_data;
	return (1);
}

void print_aciton(t_data *philo_data, char *str)
{
	printf(" %lld %d %s\n", get_time(philo_data->general_data->program_time), philo_data->name, str);
}

void	*philo(void *arg)
{
	t_data	*philo_data;

	philo_data = (t_data *)arg;
	if(philo_data->name % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo_data->left_mutex);
		print_aciton( philo_data,  "has taken a fork");
		pthread_mutex_lock(philo_data->right_mutex);
		print_aciton( philo_data,  "has taken a fork");
		print_aciton( philo_data,  "is eating");
		my_usleep(philo_data->time_to_eat);
		philo_data->last_eating_time = get_time(0);
		pthread_mutex_unlock(philo_data->left_mutex);
		pthread_mutex_unlock(philo_data->right_mutex);
		print_aciton( philo_data,  "is sleeping");
		my_usleep(philo_data->time_to_sleep);
		print_aciton( philo_data,  "is thinking");
	}
	return(0);
}

int is_dead (t_data	*philo_data)
{
	int i;

	i = 0;	
	while (get_time(0) - philo_data[i].last_eating_time < philo_data[i].time_to_die)
	{
		if (i == philo_data->general_data->philos_count)
		{
			i = -1;
		}
		i++;
	}
	printf("IS dead\n");
	return (1);
}


int	main(int argc, char **argv)
{
	t_data			*philos_data;
	pthread_mutex_t *chopsicks;
	t_general_data	general_data;
	int				i;
	if (argc == 5 || argc == 6)
	{
		if (arg_validity_check(argc, argv))
		{
			general_data.philos_count = ft_atoi(argv[1]);
			i = 0;
			philos_data = malloc(sizeof(philos_data) * general_data.philos_count);
			chopsicks = malloc(sizeof(pthread_mutex_t) * general_data.philos_count);
			while (i < general_data.philos_count)
				pthread_mutex_init(&chopsicks[i++] , 0);
			i = 0;
			while (i < general_data.philos_count)
			{
				init_args(argc, argv, &general_data, &philos_data[i], i);
				philos_data[i].left_mutex = &chopsicks[i];
				if (i == general_data.philos_count - 1)
					philos_data[i].right_mutex = &chopsicks[0];
				else
					philos_data[i].right_mutex = &chopsicks[i + 1];
				i++;
			}
			i = 0;
			general_data.program_time = get_time(0);
			while (i < general_data.philos_count)
			{
				pthread_create(&philos_data[i].thread_id, NULL, philo, &philos_data[i]);
				i++;
			} 

		}
	}
	
	/*
	while(1)
		;
	*/
	is_dead(philos_data);
	printf("Time is %lld\n", get_time(0));
	printf("game_over\n");
	return (0);
}
