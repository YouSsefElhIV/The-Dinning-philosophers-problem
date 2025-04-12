/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:16:23 by yel-haya          #+#    #+#             */
/*   Updated: 2025/03/09 23:29:10 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	creating_threads(t_philos *p)
{
	int				i;

	i = 1;
	p->info->starting_time = getting_curr_time();
	if (pthread_create(&p->info->observer, NULL, &monitoring, (void *)p) != 0)
		return (write(2, "failed to create the thread...\n", 32), 0);
	while (i < p->info->philo_number + 1)
	{
		if (pthread_create(&p->thread_id, NULL, &handler, (void *)p) != 0)
			return (write(2, "failed to create the thread...\n", 32), 0);
		p = p->next;
		i++;
	}
	return (1);
}

void	joining_threads(t_philos *philo)
{
	int	i;

	i = 0;
	if (pthread_join(philo->info->observer, NULL) != 0)
		write(2, "failed to join the thread...\n", 30);
	while (i < philo->info->philo_number)
	{
		if (pthread_join(philo->thread_id, NULL) != 0)
		{
			write(2, "failed to join the thread...\n", 30);
			break ;
		}
		philo = philo->next;
		i++;
	}
}

int	init_mutex(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->philo_number)
	{
		if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		{
			write(2, "Error init mutex\n", 18);
			return (1);
		}
		philo = philo->next;
		i++;
	}
	if (pthread_mutex_init(&(philo->info->typing_mutex), NULL) != 0
		|| pthread_mutex_init(&(philo->info->food), NULL) != 0
		|| pthread_mutex_init(&(philo->info->is_dead_mutex), NULL) != 0)
	{
		write(2, "Error init mutex\n", 18);
		return (1);
	}
	return (0);
}

void	destroy_mutex(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->philo_number)
	{
		pthread_mutex_destroy(&philo->mutex);
		philo = philo->next;
		i++;
	}
	pthread_mutex_destroy(&(philo->info->is_dead_mutex));
	pthread_mutex_destroy(&(philo->info->typing_mutex));
	pthread_mutex_destroy(&(philo->info->food));
}

int	creating_philosophers(t_philos *philo)
{
	philo = init_philo_list(philo);
	if (philo == NULL)
		return (1);
	if (creating_threads(philo) == 1)
		joining_threads(philo);
	destroy_mutex(philo);
	return (0);
}
