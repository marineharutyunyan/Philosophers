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
	philo_data->name = i+1;
	return (1);
}
int ft_str_len(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (i);

	while (str[i])
		i++;
	return (i);
}

int is_equal(char *s1, char *s2)
{
	int i;
	int s1_len;
	int s2_len;

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
	{
		return (0);
	}
}

void print_aciton(t_data *philo_data, char *str)
{
	//printf("the mutex pointer is ----------- %p\n", &philo_data->general_data->print_mutex);
	pthread_mutex_lock(&philo_data->general_data->print_mutex);
	if (!is_equal(str, "full"))
	{
		printf(" %lld %d %s\n", get_time(philo_data->general_data->program_time), philo_data->name, str);
		if (!is_equal(str, "died"))
			pthread_mutex_unlock(&philo_data->general_data->print_mutex);
	}
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
		philo_data->eating_count += 1;
		if (philo_data->general_data->must_eat_count == philo_data->eating_count)
			philo_data->is_full = 1;
		pthread_mutex_unlock(philo_data->left_mutex);
		pthread_mutex_unlock(philo_data->right_mutex);
		print_aciton( philo_data,  "is sleeping");	
		my_usleep(philo_data->time_to_sleep);
		print_aciton( philo_data,  "is thinking");
	}
	return(0);
}

int is_dead (t_data	*philos_data)
{
	int i;
	int all_are_full;
	long long	program_time;

	i = 0;
	all_are_full = 0;
	program_time = get_time(0) - philos_data[i].last_eating_time;
	while (program_time < philos_data[i].time_to_die) 
	{
		if (philos_data[i].is_full)
			all_are_full += 1;
		program_time = get_time(0) - philos_data[i].last_eating_time;
		if (i == philos_data->general_data->philos_count - 1)
		{
			i = -1;
			if(all_are_full == philos_data->general_data->philos_count)
			{
				printf("all_are_full %d ,,, philos_count %d\n", all_are_full, philos_data->general_data->philos_count);
				print_aciton(philos_data, "full");
				return (1);
			}
			all_are_full = 0;
		}
		i++;
	}
	print_aciton(philos_data, "died");
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
			philos_data = malloc(sizeof(t_data) * general_data.philos_count);
			chopsicks = malloc(sizeof(pthread_mutex_t) * general_data.philos_count);
			pthread_mutex_init(&general_data.print_mutex, 0);
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
	is_dead(philos_data);
	printf("game_over\n");
	return (0);
}
