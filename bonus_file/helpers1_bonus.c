/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:53:50 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 11:56:37 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	creating_philosophers(t_philos *philo)
{
	int	i;

	i = 0;
	philo = init_philo_list(philo);
	if (philo == NULL)
		return (1);
	create_sems(philo);
	while (i < philo->info->philo_number)
	{
		philo->proccess_id = fork();
		if (philo->proccess_id == 0)
		{
			simulation(philo);
			break ;
		}
		philo = philo->next;
		i++;
	}
	destroy_sems(philo);
	return (0);
}

int	my_usleep(long milliseconds)
{
	long	start;

	start = getting_curr_time();
	while ((getting_curr_time() - start) < milliseconds)
	{		
		usleep(500);
	}
	return (0);
}

void	free_things(t_philos *philo)
{
	t_philos	*courant;

	if (!philo)
		return ;
	courant = philo;
	while (courant->next != philo)
		courant = courant->next;
	courant->next = NULL;
	courant = philo;
	free(philo->info);
	while (philo)
	{
		courant = philo->next;
		free(philo);
		philo = courant;
	}
}

static int	spaces_check(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	if (sign < 0)
		return (-69);
	if (str[*i] < '0' || str[*i] > '9')
		return (-69);
	return (sign);
}

int	ft_atoii(const char *str)
{
	int		i;
	long	res;
	int		sign;

	res = 0;
	i = 0;
	sign = spaces_check(str, &i);
	if (sign == -69)
		return (sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (-69);
	if (res > INT_MAX || res <= -2147483648)
		return (-69);
	return (((int)res * sign));
}
