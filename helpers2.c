/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:33:20 by yel-haya          #+#    #+#             */
/*   Updated: 2025/04/12 10:55:42 by yel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	my_usleep(long milliseconds, t_philos *p)
{
	long		start;

	start = getting_curr_time();
	while ((getting_curr_time() - start) < milliseconds)
	{
		usleep(500);
		pthread_mutex_lock(&(p->info->is_dead_mutex));
		if (p->info->is_dead == 1)
		{
			pthread_mutex_unlock(&(p->info->is_dead_mutex));
			printing("died", p);
			return (0);
		}
		pthread_mutex_unlock(&(p->info->is_dead_mutex));
	}
	pthread_mutex_lock(&(p->info->is_dead_mutex));
	pthread_mutex_unlock(&(p->info->is_dead_mutex));
	return (0);
}
