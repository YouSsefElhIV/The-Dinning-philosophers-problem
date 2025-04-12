/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:49:59 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 16:16:27 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	destroy_sems(t_philos *philo)
{
	int	i;
	int	stat;

	i = 0;
	while (i < philo->info->philo_number)
	{
		waitpid(-1, &stat, 0);
		if (stat == 0)
		{
			i = 0;
			while (i < philo->info->philo_number)
			{
				kill(philo->proccess_id, SIGKILL);
				philo = philo->next;
				i++;
			}
		}
		i++;
	}
	sem_close(philo->info->typing_sem);
	sem_close(philo->info->forks);
	sem_close(philo->info->dead_sem);
	sem_close(philo->info->checking);
}

int	is_dead(t_philos *p)
{
	sem_wait(p->info->dead_sem);
	if (p->info->is_dead == 1)
	{
		sem_post(p->info->dead_sem);
		return (1);
	}
	sem_post(p->info->dead_sem);
	return (0);
}
