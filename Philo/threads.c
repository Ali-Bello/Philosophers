/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/04 14:11:31 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    printf("%ldms philo %d is sleeping\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(philo->info->time_to_sleep * 1000);
}

void   eat(t_philo *philo)
{    
}

void    think(t_philo *philo)
{
    printf("%ldms philo %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(10);
}
