/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:35:29 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 16:00:37 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	printing(char *str, t_philos *philo)
{
	sem_wait((philo->info->typing_sem));
	sem_wait((philo->info->dead_sem));
	if (philo->info->is_dead == 1)
	{
		sem_post((philo->info->dead_sem));
		sem_post((philo->info->typing_sem));
		return ;
	}
	sem_post((philo->info->dead_sem));
	printf("%li %i %s\n", getting_curr_time() - philo->info->starting_time \
	, philo->current_philo, str);
	if (str && str[0] == 'd')
	{
		sem_wait((philo->info->dead_sem));
		philo->info->is_dead = 1;
		sem_post((philo->info->dead_sem));
		return ;
	}
	sem_post((philo->info->typing_sem));
}

int	init(int ac, char **av, t_philos *philo)
{
	philo->info = (t_arguments *)malloc(sizeof(t_arguments));
	if (!philo->info)
		return (1);
	philo->info->philo_number = ft_atoii(av[1]);
	philo->info->time_to_die = ft_atoii(av[2]);
	philo->info->time_to_eat = ft_atoii(av[3]);
	philo->info->time_to_sleep = ft_atoii(av[4]);
	philo->info->is_dead = 0;
	philo->info->starting_time = getting_curr_time();
	philo->info->is_full = 0;
	if (ac == 6)
		philo->info->times_to_eat = ft_atoii(av[5]);
	else
		philo->info->times_to_eat = -1;
	if (philo->info->philo_number == 0 || philo->info->times_to_eat == 0)
		return (2);
	if (philo->info->philo_number == -69 || philo->info->time_to_die == -69 \
		|| philo->info->time_to_eat == -69 || philo->info->time_to_sleep == -69 \
		|| philo->info->times_to_eat == -69)
		return (3);
	return (0);
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
