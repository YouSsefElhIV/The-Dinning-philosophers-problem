/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:40:23 by yel-haya          #+#    #+#             */
/*   Updated: 2025/03/09 21:23:51 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(char *str, t_philos *philo)
{
	pthread_mutex_lock(&(philo->info->typing_mutex));
	pthread_mutex_lock(&(philo->info-> is_dead_mutex));
	if (philo->info->is_dead == 1)
	{
		pthread_mutex_unlock(&(philo->info->is_dead_mutex));
		pthread_mutex_unlock(&(philo->info->typing_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->info->is_dead_mutex));
	printf("%li %i %s\n", getting_curr_time() - philo->info->starting_time \
	, philo->current_philo, str);
	if (str && str[0] == 'd')
	{
		pthread_mutex_lock(&(philo->info->is_dead_mutex));
		philo->info->is_dead = 1;
		pthread_mutex_unlock(&(philo->info->is_dead_mutex));
		pthread_mutex_unlock(&(philo->info->typing_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->info->typing_mutex));
}

long	getting_curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	add_philo_to_list(t_philos *philo, t_philos *new)
{
	t_philos	*courant;

	courant = philo;
	while (courant->next != philo)
		courant = courant->next;
	new->next = philo;
	courant->next = new;
}

t_philos	*create_philo_list(t_philos *philo)
{
	t_philos	*new;
	t_philos	*head;
	int			i;

	head = philo;
	head->next = philo;
	i = 0;
	while (i < (philo)->info->philo_number - 1)
	{
		new = (t_philos *)malloc(sizeof(t_philos));
		if (!new)
			return (NULL);
		new->info = philo->info;
		add_philo_to_list(head, new);
		i++;
	}
	return (head);
}
