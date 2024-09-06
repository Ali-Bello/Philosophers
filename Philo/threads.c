/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/06 17:42:34 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    if (!philo->fork.status)
        return ;
    philo->fork.status = 0;
    philo->neighboor->fork.status = 0;
    printf("%ld %d is sleeping\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(philo->info->time_to_sleep * 1000);
}

void   eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->status_mtx);
    if (!philo->fork.status && !philo->neighboor->fork.status)
    {
        pthread_mutex_unlock(&philo->info->status_mtx);
        pthread_mutex_lock(&philo->fork.mtx);
        pthread_mutex_lock(&philo->neighboor->fork.mtx);
        philo->fork.status = 1;
        philo->neighboor->fork.status = 1;
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
        printf("%ld %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
        printf("%ld %d is eating\n",get_timestamp() - philo->info->start_time, philo->id);
        philo->last_meal_time = get_timestamp() - philo->info->start_time;
        usleep(philo->info->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->neighboor->fork.mtx);
        pthread_mutex_unlock(&philo->fork.mtx);
    }
    else
    {
        pthread_mutex_unlock(&philo->info->status_mtx);
        think(philo);
        while (philo->fork.status || philo->neighboor->fork.status)
            ;
    }
}

void    think(t_philo *philo)
{
    printf("%ld %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(10);
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
