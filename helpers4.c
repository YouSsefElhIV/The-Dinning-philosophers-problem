/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:53:00 by yel-haya          #+#    #+#             */
/*   Updated: 2025/03/09 22:08:23 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		philo->many_time_ate = 0;
		philo = philo->next;
		i++;
	}
	if (init_mutex(philo) == 1)
		return (NULL);
	return (philo);
}

int	sleeping(t_philos *philo)
{
	printing("is sleeping", philo);
	my_usleep(philo->info->time_to_sleep, philo);
	return (0);
}

int	thinking(t_philos *philo)
{
	printing("is thinking", philo);
	return (0);
}

void	work_for_one_philo(t_philos *philo)
{
	pthread_mutex_lock(&(philo->mutex));
	printing("has taken a fork", philo);
	my_usleep(philo->info->time_to_die, philo);
	printing("died", philo);
	pthread_mutex_unlock(&(philo->mutex));
}

int	is_anyone_dead(t_philos *philo)
{
	pthread_mutex_lock(&(philo->info->is_dead_mutex));
	if (philo->info->is_dead == 1)
		return (1);
	pthread_mutex_unlock(&(philo->info->is_dead_mutex));
	return (0);
}
