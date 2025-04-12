/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:55:19 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 11:57:08 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	work_for_one_philo(t_philos *philo)
{
	sem_wait(philo->info->forks);
	printing("has taken a fork", philo);
	my_usleep(philo->info->time_to_die);
	printing("died", philo);
	sem_post(philo->info->forks);
}

void	eating(t_philos *philo)
{
	printing("is eating", philo);
	sem_wait(philo->info->checking);
	philo->last_time_ate = getting_curr_time();
	philo->many_time_ate++;
	sem_post(philo->info->checking);
	my_usleep(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	sleeping(t_philos *philo)
{
	printing("is sleeping", philo);
	my_usleep(philo->info->time_to_sleep);
}

void	thinking(t_philos *philo)
{
	printing("is thinking", philo);
}

int	main(int ac, char **av)
{
	t_philos	*philo;
	int			init_result;

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
