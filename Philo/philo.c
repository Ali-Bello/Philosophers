/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 04:53:07 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/06 17:37:06 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_clean(t_info *info)
{
    if (info->philos)
        free(info->philos);
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
    i = 0;
    while (i < info->num_of_philos)
    {
        memset(&info->philos[i], 0, sizeof(t_philo));
        info->philos[i].info = info;
        info->philos[i].neighboor = &info->philos[(i + 1) % info->num_of_philos];
        info->philos[i].id = i + 1;
        info->philos[i].fork.status = 0;
        if (pthread_mutex_init(&info->philos[i].fork.mtx, NULL))
            return (ft_clean(info), 1);
        i++;
    }
    if (pthread_mutex_init(&info->status_mtx, NULL))
        return (ft_clean(info), 1);
    if (pthread_mutex_init(&info->simul_mtx, NULL))
        return (ft_clean(info), 1);
    return (0);
}

void    *activity(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->info->simul_mtx);
        if (philo->info->simul_flag)
            break;
        pthread_mutex_unlock(&philo->info->simul_mtx);
        eat(philo);
        philo_sleep(philo);
    }
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
    i = 0;
    while (i < info.num_of_philos)
    {
        info.start_time = get_timestamp();
        if (pthread_create(&info.philos[i].ptid, NULL,\
            activity, &info.philos[i]))
            return (ft_clean(&info), 0);
        i++;
    }
    azrael(&info);
    printf("here\n");
    i = 0;
    while (i < info.num_of_philos)
        pthread_join(info.philos[i++].ptid, NULL);
    ft_clean(&info);
    return (0);
}
