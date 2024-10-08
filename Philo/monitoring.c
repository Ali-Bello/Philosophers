/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:40:00 by codespace         #+#    #+#             */
/*   Updated: 2024/10/08 21:46:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t usec, t_philo *philo)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < usec)
	{
		if (philo && is_dead(philo->info))
			return ;
		usleep(100);
	}
}

int	meals_check(t_info *info)
{
	if (info->num_of_meals)
	{
		pthread_mutex_lock(&info->meals_mtx);
		if (info->meals_flag == info->num_of_philos)
		{
			pthread_mutex_lock(&info->simul_mtx);
			info->simul_flag = 1;
			pthread_mutex_unlock(&info->simul_mtx);
			pthread_mutex_unlock(&info->meals_mtx);
			return (1);
		}
		pthread_mutex_unlock(&info->meals_mtx);
	}
	return (0);
}

int	is_dead(t_info *info)
{
	pthread_mutex_lock(&info->simul_mtx);
	if (info->simul_flag)
	{
		pthread_mutex_unlock(&info->simul_mtx);
		return (1);
	}
	pthread_mutex_unlock(&info->simul_mtx);
	return (0);
}

int	check_death(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_lock(&info->philos[i].time_mtx);
		if (info->philos[i].last_meal_time && get_timestamp()
			- info->philos[i].last_meal_time >= info->time_to_die)
		{
			pthread_mutex_lock(&info->simul_mtx);
			info->simul_flag = 1;
			pthread_mutex_unlock(&info->simul_mtx);
			pthread_mutex_lock(&info->print_mtx);
			printf("%ld %d %s\n", get_timestamp() - info->start_time, i + 1, \
				RED "died" RESET);
			pthread_mutex_unlock(&info->print_mtx);
			pthread_mutex_unlock(&info->philos[i].time_mtx);
			return (1);
		}
		pthread_mutex_unlock(&info->philos[i].time_mtx);
		i++;
	}
	return (0);
}

void	monitor(t_info *info)
{
	while (!is_dead(info))
	{
		if (check_death(info) || meals_check(info))
			break ;
		ft_usleep(1, NULL);
	}
}
