#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

extern pthread_mutex_t mutex;

typedef struct s_general_data
{

	int				philos_count;
	long long		program_time;
	int				must_eat_count;
	pthread_mutex_t	print_mutex;
}		t_general_data;

typedef struct s_data
{
	int				name;
	long long		last_eating_time;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num;
	int				is_dead;
	int				is_full;
	int				eating_count;
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
	pthread_t		thread_id;
	t_general_data	*general_data;
}		t_data;

long long	get_time(long long last_eating_time);
int			ft_isdigit(char c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
int			ft_str_len(char *str);
int			is_equal(char *s1, char *s2);
void		my_usleep(int requested_time);
int			arg_validity_check(int argc, char **argv);

#endif