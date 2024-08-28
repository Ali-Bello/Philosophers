/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 04:53:07 by aderraj           #+#    #+#             */
/*   Updated: 2024/08/28 03:50:19 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_clean(t_info *info)
{
    if (info->philos)
        free(info->philos);
    if (info->forks)
        free(info->forks);
    memset(info, 0, sizeof(t_info));
}
long    get_timestamp()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int init_objects(t_info *info)
{
    int i;

    info->philos = malloc(sizeof(t_philo) * info->num_of_philos);
    if (!info->philos)
        return (1);
    info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
    if (!info->forks)
        return (ft_clean(info), 1);
    i = 0;
    while (i < info->num_of_philos)
    {
        memset(&info->philos[i], 0, sizeof(t_philo));
        info->philos[i].info = info;
        info->philos[i].philo_no = i + 1;
        if (pthread_mutex_init(&info->forks[i], NULL))
            return (ft_clean(info), 1);
        i++;
    }
    if (pthread_mutex_init(&info->time_mutex, NULL))
        return (ft_clean(info), 1);
    return (0);
}

void    *activity(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->info->time_mutex);
    while (!philo->info->death_flag)
    {
        long time = get_timestamp() - philo->info->start_time;
        printf("%ldms philo %d is thinking %d\n", time, philo->philo_no, philo->status);
        if (time > philo->info->time_to_eat)
        {
            philo->info->death_flag = 1;
            printf("%ldms philo %d is dead\n", time, philo->philo_no);
        }   
    }
    pthread_mutex_unlock(&philo->info->time_mutex);
    return (NULL);
}

int main(int ac, char **av)
{
    t_info info;
    int i;

    memset(&info, 0, sizeof(t_info));
    if (check_input(ac, av, &info))
        return (0);
    if (init_objects(&info))
        return (0);
    info.start_time = get_timestamp();
    i = 0;
    while (i < info.num_of_philos)
    {
        if (pthread_create(&info.philos[i].ptid, NULL,\
            activity, &info.philos[i]))
            return (ft_clean(&info), 0);
        i++;
    }
    i = 0;
    while (i < info.num_of_philos)
        pthread_join(info.philos[i++].ptid, NULL);
    ft_clean(&info);
    return (0);
}
