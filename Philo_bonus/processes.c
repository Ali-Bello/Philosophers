/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 04:23:55 by codespace         #+#    #+#             */
/*   Updated: 2024/10/31 15:33:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_logs(t_info *info, int id, char *s)
{
	sem_wait(info->write_sem);
	printf("%ld %d %s\n", get_timestamp() - info->start_time, id, s);
	sem_post(info->write_sem);
}

void	pickup_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_logs(philo->info, philo->id, "has taken a fork");
	if (philo->info->num_of_philos == 1)
		return ;
	sem_wait(philo->info->forks);
	print_logs(philo->info, philo->id, "has taken a fork");
}

void	sleep_think(t_philo *philo)
{
	print_logs(philo->info, philo->id, "is sleeping");
	ft_usleep(philo->info->time_to_sleep, philo);
	print_logs(philo->info, philo->id, "is thinking");
	ft_usleep(1, philo);
}

void	eat_release_forks(t_philo *philo)
{
	sem_wait(philo->time_lock);
	philo->last_meal_time = get_timestamp();
	sem_post(philo->time_lock);
	print_logs(philo->info, philo->id, "is eating");
	ft_usleep(philo->info->time_to_eat, philo);
	philo->meals_eaten++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

int	activity(t_philo *philo)
{
	if (philo->info->num_of_philos == 1)
	{
		pickup_forks(philo);
		ft_usleep(philo->info->time_to_die, NULL);
		return (1);
	}
	if (pthread_create(&philo->death_tid, NULL, death_check, philo))
		return (printf(RED "Error creating thread\n" RESET), -1);
	while (!is_dead(philo))
	{
		if (philo->info->num_of_meals
			&& philo->meals_eaten == philo->info->num_of_meals)
			return (clean_child(philo), 0);
		sem_wait(philo->info->max_philos);
		pickup_forks(philo);
		eat_release_forks(philo);
		sem_post(philo->info->max_philos);
		sleep_think(philo);
	}
	return (clean_child(philo), 1);
}
