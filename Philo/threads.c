/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/14 22:59:24 by aderraj          ###   ########.fr       */
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

void    philo_sleep(t_philo *philo)
{
    printf("%ld %d is sleeping\n",get_timestamp() - philo->info->start_time, philo->id);
    ft_usleep(philo->info->time_to_sleep);
}

void    pickup_forks(t_philo *philo)
{
    if (philo->id != philo->info->num_of_philos)
    {
        pthread_mutex_lock(&philo->info->forks[philo->id - 1]);
        printf("[%d] time elapsed = %ld\n", philo->id, get_timestamp() - philo->last_meal_time);
        if (get_timestamp() - philo->last_meal_time >= (size_t)philo->info->time_to_die)
        {
            pthread_mutex_lock(&philo->info->status_mtx);
            philo->info->simul_flag = 1;
            pthread_mutex_unlock(&philo->info->status_mtx);
        }
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
        pthread_mutex_lock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);   
    }
    else
    {
        pthread_mutex_lock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
        printf("[%d] time elapsed = %ld\n", philo->id,  get_timestamp() - philo->last_meal_time);
        if (get_timestamp() - philo->last_meal_time >= (size_t)philo->info->time_to_die)
        {
            pthread_mutex_lock(&philo->info->status_mtx);
            philo->info->simul_flag = 1;
            pthread_mutex_unlock(&philo->info->status_mtx);
        }
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
        pthread_mutex_lock(&philo->info->forks[philo->id - 1]);
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
    }
    philo->last_meal_time = get_timestamp();
}

void    eat(t_philo *philo)
{
    pickup_forks(philo);
    philo->meals_eaten++;
    printf("%ld %d is eating\n",get_timestamp() - philo->info->start_time, philo->id);
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
}

void    think(t_philo *philo)
{
    printf("%ld %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
}

