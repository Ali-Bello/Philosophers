/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 04:53:23 by codespace         #+#    #+#             */
/*   Updated: 2024/10/31 15:42:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	sem_wait(philo->death_sem);
	if (philo->death_flag)
	{
		sem_post(philo->death_sem);
		return (1);
	}
	sem_post(philo->death_sem);
	return (0);
}

void	*death_check(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_detach(philo->death_tid);
	while (1)
	{
		sem_wait(philo->time_lock);
		if (philo->last_meal_time && get_timestamp()
			- philo->last_meal_time >= philo->info->time_to_die)
		{
			sem_post(philo->time_lock);
			sem_wait(philo->death_sem);
			philo->death_flag = 1;
			sem_post(philo->death_sem);
			return (NULL);
		}
		sem_post(philo->time_lock);
		ft_usleep(50, NULL);
	}
	return (NULL);
}

void	stop_processes(t_info *info, int status, int i)
{
	int	j;

	if ((status >> 8 & 0xFF) == 1)
	{
		j = 0;
		print_logs(info, i + 1, RED "is dead" RESET);
		while (j < info->num_of_philos)
		{
			sem_close(info->philos[j].time_lock);
			sem_close(info->philos[j].death_sem);
			kill(info->philos[j++].pid, SIGKILL);
		}
		ft_clean(info);
		exit(0);
	}
	else if (i == info->num_of_philos - 1)
	{
		ft_clean(info);
		exit(0);
	}
}

void	table_monitor(t_info *info)
{
	int	status;
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			if (waitpid(info->philos[i].pid, &status, WNOHANG) > 0)
				stop_processes(info, status, i);
			i++;
		}
		ft_usleep(1, NULL);
	}
}

void	clean_child(t_philo *philo)
{
	sem_close(philo->time_lock);
	sem_close(philo->death_sem);
	ft_clean(philo->info);
}
