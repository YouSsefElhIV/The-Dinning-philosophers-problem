/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:15:14 by yel-haya          #+#    #+#             */
/*   Updated: 2025/03/09 22:17:54 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_argments
{
	int				philo_number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_to_eat;
	int				is_dead;
	int				is_full;
	long			starting_time;
	pthread_t		observer;
	pthread_mutex_t	food;
	pthread_mutex_t	typing_mutex;
	pthread_mutex_t	is_dead_mutex;
}	t_arguments;

typedef struct s_philos
{
	pthread_t		thread_id;
	int				current_philo;
	int				many_time_ate;
	long			last_time_ate;
	t_arguments		*info;
	pthread_mutex_t	mutex;
	struct s_philos	*next;
}	t_philos;

int			ft_atoii(const char *str);
long		getting_curr_time(void);
int			init(int ac, char **av, t_philos *args);
void		*handler(void *m);
int			creating_philosophers(t_philos *args);
void		free_things(t_philos *args);
void		destroy_mutex(t_philos *args);
void		*monitoring(void *args);
int			eating(t_philos *args);
int			sleeping(t_philos *args);
int			thinking(t_philos *args);
int			my_usleep(long time_to_sleep, t_philos *philo);
t_philos	*init_philo_list(t_philos *args);
int			init_mutex(t_philos *args);
t_philos	*create_philo_list(t_philos *args);
void		work_for_one_philo(t_philos *args);
void		printing(char *str, t_philos *args);
int			is_anyone_dead(t_philos *philo);

#endif