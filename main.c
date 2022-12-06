#include "philosophers.h"

int	arg_validity_check(int argc, char **argv)
{
	int	i;

	i == 1;
	while (i == argc - 1)
	{
		if (ft_isdigit(argv[i]))
		{
			i++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

int	init_args(int argc, char **argv, t_data *philo_data, t_general_data *general_data)
{
	if (arg_validity_check(argc, argv))
	{
		if (argc == 5)
			philo_data.eating_count = argv[5];
		general_data.philos_count = argv[1];
		philo_data.time_to_die = argv[2];
		philo_data.time_to_eat = argv[3];
		philo_data.time_to_sleep = argv[4];
	}
	else
	{
		return (0);
	}
	return (1);
}
pthread *create_philo ()
{

}
int	main(int argc, char **argv)
{
	t_data			philo_data;
	t_general_data	general_data;
	int				i;
	int				**philosophers;

	if (argc == 4 || argc == 5)
	{
		if (init_args(argc, argv, &philo_data, &general_data))
		{
			i = 0;
			while (i < general_data.philos_count)
			{
				philosophers[i] = create_philo();
				pthread_create()
				
				pthread_create(&thread_id, NULL, my_thread_fun, data);

				i++;
			}
			
		}
	}
	return (0);
}









/*
void	*my_thread_fun(void	*arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	while (data->num < 10)
	{	
		data->num++;
		printf("value was incremented %d\n", data->num);
		pthread_mutex_unlock(&data->mutex);
		pthread_mutex_lock(&data->mutex);
	}
	pthread_mutex_unlock(&data->mutex);
	return (0);
}

int	main(void)
{
	void			*returned_val;
	t_data			*data;
	pthread_t		thread_id;

	data = malloc(sizeof(t_data));
	data->num = 0;
	pthread_mutex_init(&data->mutex, 0);
	pthread_create(&thread_id, NULL, my_thread_fun, data);
	pthread_mutex_lock(&data->mutex);
	while (data->num < 10)
	{
		printf("Printed value is %d\n", data->num);
		pthread_mutex_unlock(&data->mutex);
		pthread_mutex_lock(&data->mutex);
	}
	pthread_mutex_unlock(&data->mutex);
	pthread_join(thread_id, &returned_val);
	pthread_detach(thread_id);
	printf("After all it's the end!%d\n", (int)returned_val);
	free(data);
	return (0);
}
*/