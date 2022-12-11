#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_general_data
{
	int	philos_count;
}		t_general_data;

typedef struct s_data
{
	int				name;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num;
	int				is_dead;
	int				eating_count;
	pthread_mutex_t	left_mutex;
	pthread_mutex_t	right_mutex;
	pthread_t		thread_id;
}		t_data;

int	ft_isdigit(char c);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

#endif