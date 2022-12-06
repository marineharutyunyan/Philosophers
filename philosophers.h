#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
# include <pthread.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_general_data
{
	int	philos_count;
}		t_general_data;

typedef struct s_data
{
	pthread_mutex_t	mutex_max;
	pthread_mutex_t	mutex_min;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num;
	int				is_dead;
	int				eating_count;
}		t_data;
#endif