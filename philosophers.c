/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:16:11 by yel-haya          #+#    #+#             */
/*   Updated: 2025/03/10 00:54:57 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_philos *philo)
{
	if (philo->current_philo == philo->info->philo_number)
		pthread_mutex_lock(&(philo->next->mutex));
	else
		pthread_mutex_lock(&(philo->mutex));
	printing("has taken a fork", philo);
	if (philo->current_philo == philo->info->philo_number)
		pthread_mutex_lock(&(philo->mutex));
	else
		pthread_mutex_lock(&(philo->next->mutex));
	printing("has taken a fork", philo);
	printing("is eating", philo);
	pthread_mutex_lock(&(philo->info->food));
	philo->many_time_ate++;
	philo->last_time_ate = getting_curr_time();
	pthread_mutex_unlock(&(philo->info->food));
	my_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->next->mutex));
	pthread_mutex_unlock(&(philo->mutex));
	return (0);
}

void	checking(t_philos *philo)
{
	pthread_mutex_lock(&(philo->info->food));
	if (getting_curr_time() - philo->last_time_ate > philo->info->time_to_die)
	{
		printing("died", philo);
		pthread_mutex_lock(&(philo->info->is_dead_mutex));
		philo->info->is_dead = 1;
		pthread_mutex_unlock(&(philo->info->is_dead_mutex));
	}
	pthread_mutex_unlock(&(philo->info->food));
	pthread_mutex_lock(&(philo->info->food));
	if (philo->info->times_to_eat != -1 \
		&& philo->many_time_ate > philo->info->times_to_eat)
	{
		pthread_mutex_lock(&(philo->info->is_dead_mutex));
		philo->info->is_dead = 1;
		philo->info->is_full = 1;
		pthread_mutex_unlock(&(philo->info->is_dead_mutex));
	}
	pthread_mutex_unlock(&(philo->info->food));
}

void	*monitoring(void *m)
{
	t_philos	*philo;

	philo = (t_philos *)m;
	while (1)
	{
		pthread_mutex_lock(&(philo->info->is_dead_mutex));
		if (philo->info->is_dead == 1)
		{
			pthread_mutex_unlock(&(philo->info->is_dead_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->info->is_dead_mutex));
		checking(philo);
		philo = philo->next;
	}
	my_usleep(10, philo);
	return (NULL);
}

void	*handler(void *m)
{
	t_philos		*philo;

	philo = (t_philos *)m;
	if (philo->info->philo_number == 1)
		return (work_for_one_philo(philo), NULL);
	if (philo->current_philo % 2 == 0)
		my_usleep(1, philo);
	pthread_mutex_lock(&(philo->info->food));
	philo->last_time_ate = getting_curr_time();
	pthread_mutex_unlock(&(philo->info->food));
	pthread_mutex_lock(&(philo->info->is_dead_mutex));
	while (philo->info->is_dead == 0)
	{
		pthread_mutex_unlock(&(philo->info->is_dead_mutex));
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&(philo->info->is_dead_mutex));
	}
	pthread_mutex_unlock(&(philo->info->is_dead_mutex));
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos		*philo;
	int				init_result;

	philo = (t_philos *)malloc(sizeof(t_philos));
	if (!philo)
		return (0);
	if (ac < 5 || ac > 6)
		return (free(philo), write(2, "Syntax: ./philo a b c d [e]\n", 29), 1);
	init_result = init(ac, av, philo);
	if (init_result == 1)
		return (free(philo->info), free(philo) \
		, write(2, "Error With Malloc\n", 18), 1);
	else if (init_result == 2)
		return (free(philo->info), free(philo), 0);
	else if (init_result == 3)
		return (free(philo->info), free(philo) \
		, write(2, "Invalid Input\n", 15), 1);
	if (creating_philosophers(philo) == 1)
	{
		write(2, "Error...\n", 9);
		return (free_things(philo), 1);
	}
	return (free_things(philo), 0);
}
