/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 03:08:33 by marvin            #+#    #+#             */
/*   Updated: 2024/10/06 22:05:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(size_t usec, t_philo *philo)
{
    size_t  start;

    start  = get_timestamp();
    while ((get_timestamp() - start) < usec)
    {
        if (philo && is_dead(philo->info))
            return ;
        usleep(100);
    }
}

void    print_logs(t_info *info, int id, char *s)
{
    if (is_dead(info))
        return ;
    pthread_mutex_lock(&info->print_mtx);
    printf("%ld %d %s\n", get_timestamp() - info->start_time, id, s);
    pthread_mutex_unlock(&info->print_mtx);
}

void    pickup_forks(t_philo *philo)
{
    pthread_mutex_t *f1;
    pthread_mutex_t *f2;


    f1 = &philo->info->forks[philo->id - 1];
    f2 = &philo->info->forks[philo->id % philo->info->num_of_philos];
    if (philo->id % 2)
    {
        f1 = &philo->info->forks[philo->id % philo->info->num_of_philos];
        f2 = &philo->info->forks[philo->id - 1];
    }
    pthread_mutex_lock(f1);
    print_logs(philo->info, philo->id, "has taken a fork");
    pthread_mutex_lock(f2);
    print_logs(philo->info, philo->id, "has taken a fork");
}

void    release_forks(t_philo *philo)
{
    if (philo->id % 2)
    {
        pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);
        pthread_mutex_unlock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
    }
    else
    {
        pthread_mutex_unlock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
        pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);
    }
}

void    eat(t_philo *philo)
{
    pickup_forks(philo);
    print_logs(philo->info, philo->id, "is eating");
    pthread_mutex_lock(&philo->time_mtx);
    philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->time_mtx);
    ft_usleep(philo->info->time_to_eat, philo);

    philo->meals_eaten++;
    if (philo->info->num_of_meals && 
        philo->meals_eaten == philo->info->num_of_meals)
    {
        pthread_mutex_lock(&philo->info->meals_mtx);
        philo->info->meals_flag++;
        pthread_mutex_unlock(&philo->info->meals_mtx);
    }
    release_forks(philo);
}

void    philo_sleep(t_philo *philo)
{
    print_logs(philo->info, philo->id, "is sleeping");
    ft_usleep(philo->info->time_to_sleep, philo);
}
