/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:56:02 by marvin            #+#    #+#             */
/*   Updated: 2024/10/06 22:02:48 by marvin           ###   ########.fr       */
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

time_t    get_timestamp()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int init_objects(t_info *info)
{
    int i;

    info->philos = malloc(sizeof(t_philo) * info->num_of_philos);
    info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
    if (!info->philos || !info->forks)
        return (ft_clean(info), 1);
    i = 0;
    while (i < info->num_of_philos)
    {
        memset(&info->philos[i], 0, sizeof(t_philo));
        info->philos[i].info = info;
        info->philos[i].id = i + 1;
        pthread_mutex_init(&info->philos[i].time_mtx, NULL);
        pthread_mutex_init(&info->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&info->meals_mtx, NULL);
    pthread_mutex_init(&info->simul_mtx, NULL);
    pthread_mutex_init(&info->print_mtx, NULL);
    return (0);
}

void	*activity(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_dead(philo->info))
	{
        if (philo->info->num_of_meals && philo->meals_eaten == philo->info->num_of_meals)
            break ;
		eat(philo);
		philo_sleep(philo);
		print_logs(philo->info, philo->id, "is thinking");
		ft_usleep(1, philo);
	}
	return (NULL);
}

int main(int ac, char **av)
{
    t_info  info;
    int     i;

    memset(&info, 0, sizeof(t_info));
    if (check_input(ac, av, &info) || init_objects(&info))
        return (-1);
    info.start_time = get_timestamp();
	i = 0;
	while (i < info.num_of_philos)
	{
		if (pthread_create(&info.philos[i].ptid, NULL,\
            activity, &info.philos[i]))
        	return (ft_clean(&info), 0);
		ft_usleep(1, NULL);
		i++;
	}
    monitor(&info);
	i = 0;
	while (i < info.num_of_philos)
        pthread_join(info.philos[i++].ptid, NULL);
    ft_clean(&info);
    return (0);
}
