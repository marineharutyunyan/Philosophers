#include "philosophers.h"

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

int	init_args(int argc, char **argv, t_data philo_data, int i)
{
	if (argc == 6)
		philo_data.eating_count = ft_atoi(argv[5]);
	philo_data.time_to_die = ft_atoi(argv[2]);
	philo_data.time_to_eat = ft_atoi(argv[3]);
	philo_data.time_to_sleep = ft_atoi(argv[4]);
	philo_data.name = i;
	return (1);
}

void	*philo(void *arg)
{
	t_data	*philo_data;
	int i; 

	philo_data = (t_data *)arg;
	i = 0;
	while (1)
	{
		printf(" %d has taken a fork\n", philo_data->name);
		i++;
		/*printf(" %d is eating", philo_data->name);
		printf(" %d is sleeping", philo_data->name);
		printf(" %d is thinking", philo_data->name);*/
	}
}

int is_dead (int time_to_eat )
{
	(void)time_to_eat;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			*philos_data;
	t_general_data	general_data;
	int				i;
	if (argc == 5 || argc == 6)
	{
		if (arg_validity_check(argc, argv))
		{
			general_data.philos_count = ft_atoi(argv[1]);
			i = 0;
			philos_data = malloc(sizeof(philos_data) * general_data.philos_count);
			printf("hello there are %d phylosophers\n", general_data.philos_count);
			while (i < general_data.philos_count)
			{
				init_args(argc, argv, philos_data[i], i);
				pthread_create(&philos_data[i].thread_id, NULL, philo, &philos_data[i]);
				if (i == 1)
					pthread_mutex_init(&philos_data[i].left_mutex, 0);
				else
					philos_data[i].left_mutex = philos_data[i-1].right_mutex;
				if (i == general_data.philos_count - 1)
					philos_data[i].right_mutex = philos_data[0].left_mutex;
				else
					pthread_mutex_init(&philos_data[i].right_mutex, 0);
				i++;
			}
		}
	}
	return (0);
}
