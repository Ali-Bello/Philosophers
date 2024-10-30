/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 04:23:55 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 14:39:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_logs(t_info *info, int id, char *s)
{
	sem_wait(info->write_sem);
	printf("%ld %d %s\n", get_timestamp() - info->start_time, id, s);
	sem_post(info->write_sem);
}

void    pickup_forks(t_philo *philo)
{
    sem_wait(philo->info->forks);
    print_logs(philo->info, philo->id, "has taken a fork");
	sem_wait(philo->info->forks);
	print_logs(philo->info, philo->id, "has taken a fork");
}

void    sleep_think(t_philo *philo)
{
    print_logs(philo->info, philo->id, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
	print_logs(philo->info, philo->id, "is thinking");
	ft_usleep(1);
}

void    eat_release_forks(t_philo *philo)
{
	sem_wait(philo->time_lock);
	philo->last_meal_time = get_timestamp();
	sem_post(philo->time_lock);
    print_logs(philo->info, philo->id, "is eating");
	ft_usleep(philo->info->time_to_eat);
    sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

int activity(t_philo *philo)
{
	if (pthread_create(&philo->death_tid, NULL, death_check, philo))
		return (-1);
	pthread_detach(philo->death_tid);
	while (1)
	{
        sem_wait(philo->info->max_philos);
        pickup_forks(philo);
        eat_release_forks(philo);
        sem_post(philo->info->max_philos);
        sleep_think(philo);
	}
	return (0);
}
