#include "philosophers.h"

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
