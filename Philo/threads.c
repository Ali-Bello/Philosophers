/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 03:08:33 by marvin            #+#    #+#             */
/*   Updated: 2024/10/05 04:24:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(size_t usec)
{
    size_t  start;

    start  = get_timestamp();
    while ((get_timestamp() - start) < usec)
     usleep(649);
}

void    print_logs(size_t start_time, int id, char *s)
{
    printf("%ld %d %s\n", get_timestamp() - start_time, id, s);
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
    print_logs(philo->info->start_time, philo->id, "has taken a fork");
    pthread_mutex_lock(f2);
    print_logs(philo->info->start_time, philo->id, "has taken a fork");
    pthread_mutex_lock(&philo->time_mtx);
    philo->last_meal_time = get_timestamp();
    pthread_mutex_unlock(&philo->time_mtx);
}

void    release_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
        pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);
    }
    else
    {
        pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);   
        pthread_mutex_unlock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
    }
}

void    eat(t_philo *philo)
{
    pickup_forks(philo);
    print_logs(philo->info->start_time, philo->id, "is eating");
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_lock(&philo->meals_mtx);
    philo->meals_eaten++;
    if (philo->info->num_of_meals && philo->meals_eaten == philo->info->num_of_meals)
    {
        pthread_mutex_lock(&philo->info->meals_mtx);
        philo->info->meals_flag++;
        printf(BOLD RED"%dhere\n"RESET, philo->info->meals_flag);
        pthread_mutex_unlock(&philo->info->meals_mtx);
    }
    pthread_mutex_unlock(&philo->meals_mtx);
    release_forks(philo);
}

void    philo_sleep(t_philo *philo)
{
    print_logs(philo->info->start_time, philo->id, "is sleeping");
    ft_usleep(philo->info->time_to_sleep);
}
