#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
# include <pthread.h>

typedef struct s_data{
	pthread_mutex_t	mutex;
	int				num;
}		t_data;
#endif