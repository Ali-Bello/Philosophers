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
        pthread_mutex_init(&info->philos[i].meals_mtx, NULL);
        pthread_mutex_init(&info->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&info->meals_mtx, NULL);
    pthread_mutex_init(&info->simul_mtx, NULL);
    return (0);
}

void	*activity(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
        pthread_mutex_lock(&philo->info->simul_mtx);
		if (philo->info->simul_flag)
		{
        	pthread_mutex_unlock(&philo->info->simul_mtx);
			break;
		}
        pthread_mutex_unlock(&philo->info->simul_mtx);
		eat(philo);
		philo_sleep(philo);
		print_logs(philo->info->start_time, philo->id, "is thinking");
		usleep(15);
	}
	return (NULL);
}


int	check_death(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_lock(&info->philos[i].time_mtx);
		if (get_timestamp() - info->philos[i].last_meal_time > info->time_to_die)
		{
			pthread_mutex_lock(&info->simul_mtx);
			info->simul_flag = 1;
			pthread_mutex_unlock(&info->simul_mtx);
			print_logs(info->start_time, i + 1, RED"died"RESET);
			pthread_mutex_unlock(&info->philos[i].time_mtx);
			return (1);
		}
		pthread_mutex_unlock(&info->philos[i].time_mtx);
		i++;
	}
	return (0);
}

void	monitor(t_info *info)
{
	int	flag;

	flag = 0;
	while (1)
	{
		if (check_death(info))
			break;
		pthread_mutex_lock(&info->meals_mtx);
		if (info->num_of_meals && info->meals_flag >= info->num_of_meals)
		{
			flag = 1;
			pthread_mutex_lock(&info->simul_mtx);
			info->simul_flag = 1;
			pthread_mutex_unlock(&info->simul_mtx);
		}
		pthread_mutex_unlock(&info->meals_mtx);
		if (flag)
			break;
		usleep(1000);
	}
}


int main(int ac, char **av)
{
    t_info  info;
    int     i;

    memset(&info, 0, sizeof(t_info));
    if (check_input(ac, av, &info) || init_objects(&info))
        return (0);
    info.start_time = get_timestamp();
	i = 0;
	while (i < info.num_of_philos)
	{
        pthread_mutex_lock(&info.philos[i].time_mtx);
        info.philos[i].last_meal_time = info.start_time;
        pthread_mutex_unlock(&info.philos[i].time_mtx);
		if (pthread_create(&info.philos[i].ptid, NULL,\
            activity, &info.philos[i]))
        	return (ft_clean(&info), 0);
		usleep(50);
		i++;
	}
    monitor(&info);
	i = 0;
	while (i < info.num_of_philos)
        pthread_join(info.philos[i++].ptid, NULL);
    ft_clean(&info);
    return (0);
}
