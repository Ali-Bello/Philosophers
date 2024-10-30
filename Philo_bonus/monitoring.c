/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 04:53:23 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 14:53:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    *death_check(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (1)
    {
        sem_wait(philo->time_lock);
        if (philo->last_meal_time && get_timestamp() - philo->last_meal_time >= philo->info->time_to_die)
        {
	        sem_post(philo->time_lock);
            exit(1);
        }
        sem_post(philo->time_lock);
        ft_usleep(10);
    }
    return (NULL);
}

void    table_monitor(t_info *info)
{
    int status;
    int i;
    int j;

    while (1)
    {
        i = 0;
        while (i < info->num_of_philos)
        {
            if (waitpid(info->philos[i].pid, &status, WNOHANG) > 0)
            {
                if ((status >> 8 & 0xFF) == 1)
                {
                    j = 0;
                    print_logs(info, i + 1, RED"is dead"RESET);
                    while (j < info->num_of_philos)
                        kill(info->philos[j++].pid, SIGTERM);
                    exit(0);
                }
            }
            i++;
        }
        ft_usleep(1);
    }    
}
