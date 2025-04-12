/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:52:34 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 16:26:28 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_philos	*init_philo_list(t_philos *philo)
{
	int				i;

	i = 1;
	philo = create_philo_list(philo);
	if (!philo)
		return (NULL);
	while (i < philo->info->philo_number + 1)
	{
		philo->last_time_ate = getting_curr_time();
		philo->current_philo = i;
		philo->proccess_id = -1;
		philo->many_time_ate = 0;
		philo = philo->next;
		i++;
	}
	return (philo);
}

void	*monitoring(void *m)
{
	t_philos	*p;

	p = (t_philos *)m;
	while (69)
	{
		if (is_dead(p) == 1)
			break ;
		sem_wait(p->info->checking);
		if (getting_curr_time() - p->last_time_ate > p->info->time_to_die)
		{
			printing("died", p);
			exit (0);
		}
		if (p->info->times_to_eat != -1 \
			&& p->many_time_ate > p->info->times_to_eat)
		{
			sem_wait(p->info->dead_sem);
			p->info->is_dead = 1;
			p->info->is_full = 1;
			sem_post(p->info->dead_sem);
		}
		sem_post(p->info->checking);
	}
	my_usleep(10);
	return (NULL);
}

void	monitoring_creation(t_philos *philo)
{
	if (pthread_create(&philo->observer, NULL, &monitoring, (void *)philo) != 0)
		write(2, "failed to create the thread...\n", 32);
}

void	simulation(t_philos *philo)
{
	if (philo->info->philo_number == 1)
	{
		work_for_one_philo(philo);
		exit (0);
	}
	if (philo->current_philo % 2 == 0)
		my_usleep (1);
	monitoring_creation(philo);
	while (69)
	{
		if (is_dead(philo) == 1)
			break ;
		sem_wait(philo->info->forks);
		printing("has taken a fork", philo);
		sem_wait(philo->info->forks);
		printing("has taken a fork", philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	if (pthread_detach(philo->observer) != 0)
		write(2, "failed to detach the thread...\n", 30);
}

void	create_sems(t_philos *philo)
{
	sem_unlink("typing_sem");
	sem_unlink("forks");
	sem_unlink("checking");
	sem_unlink("dead_sem");
	philo->info->dead_sem = sem_open("dead_sem", O_CREAT, 0600, 1);
	philo->info->typing_sem = sem_open("typing_sem", O_CREAT, 0600, 1);
	philo->info->checking = sem_open("checking", O_CREAT, 0600, 1);
	philo->info->forks = sem_open("forks", \
		O_CREAT, 0600, philo->info->philo_number);
}
