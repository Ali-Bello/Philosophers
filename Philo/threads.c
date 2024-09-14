/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/14 03:03:44 by aderraj          ###   ########.fr       */
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
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
        pthread_mutex_lock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);   
    }
    else
    {
        pthread_mutex_lock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
        pthread_mutex_lock(&philo->info->forks[philo->id - 1]);
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
    }
}

void    eat(t_philo *philo)
{
    pickup_forks(philo);
    printf("%ld %d is eating\n",get_timestamp() - philo->info->start_time, philo->id);
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->info->forks[philo->id % philo->info->num_of_philos]);
}

void    think(t_philo *philo)
{
    printf("%ld %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
}

void    azrael(t_info *info)
{
    size_t  current_time;

    while (1)
    {
        pthread_mutex_lock(&info->simul_mtx);
        if (info->simul_flag)
            break;
        pthread_mutex_unlock(&info->simul_mtx);
        current_time = get_timestamp() - info->start_time;
        for (int i = 0; i < info->num_of_philos; i++)
        {
            printf(BOLD RED"die time = %ld\n"RESET, current_time - info->philos[i].last_meal_time);
            if (current_time - info->philos[i].last_meal_time >= (size_t)info->time_to_die)
            {
                printf("%ld %d is dead\n",get_timestamp() - info->start_time, info->philos[i].id);
                pthread_mutex_lock(&info->simul_mtx);
                info->simul_flag = 1;
                pthread_mutex_unlock(&info->simul_mtx);
                break;
            }
        }
        usleep(info->time_to_die * 1000);
    }
}
