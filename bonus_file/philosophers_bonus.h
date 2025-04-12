/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:51:07 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 15:23:23 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_argments
{
	int		philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		times_to_eat;
	int		is_dead;
	int		is_full;
	long	starting_time;
	sem_t	*typing_sem;
	sem_t	*checking;
	sem_t	*forks;
	sem_t	*dead_sem;
}	t_arguments;

typedef struct s_philos
{
	pid_t			proccess_id;
	int				current_philo;
	int				many_time_ate;
	long			last_time_ate;
	t_arguments		*info;
	pthread_t		observer;
	struct s_philos	*next;
}	t_philos;

int			ft_atoii(const char *str);
long		getting_curr_time(void);
int			init(int ac, char **av, t_philos *args);
int			creating_philosophers(t_philos *args);
t_philos	*init_philo_list(t_philos *philo);
void		free_things(t_philos *args);
void		printing(char *str, t_philos *p);
t_philos	*create_philo_list(t_philos *philo);
void		simulation(t_philos *p);
int			my_usleep(long n);
void		eating(t_philos *philo);
void		sleeping(t_philos *philo);
void		thinking(t_philos *philo);
void		create_sems(t_philos *philo);
void		destroy_sems(t_philos *philo);
void		work_for_one_philo(t_philos *philo);
int			is_dead(t_philos *philo);

#endif
