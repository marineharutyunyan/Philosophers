#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

void	*my_thread_fun(void	*vargp)
{
	int	*num;

	num = vargp;
	while (*num < 3)
	{
		(*num)++;
		printf("value was incremented %d\n", *num);
	}
	return (0);
}

int	main(void)
{
	int			num;
	pthread_t	thread_id;
	void		*returned_val;

	num = 0;
	pthread_create(&thread_id, NULL, my_thread_fun, &num);
	while (num < 3)
		printf("Printed value is %d\n", num);
	pthread_join(thread_id, &returned_val);
	//pthread_detach(thread_id);
	printf("After all it's the end!%d\n", (int)returned_val);
	return (0);
}
