#include "philo.h"


int meals_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mtx);
	if (philo->info->num_of_meals && philo->meals_eaten > philo->info->num_of_meals)
	{
		pthread_mutex_lock(&philo->info->simul_mtx);
		philo->info->simul_flag = 1;
		pthread_mutex_unlock(&philo->info->simul_mtx);
		pthread_mutex_unlock(&philo->meals_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals_mtx);
	return (0);
}

int is_dead(t_info *info)
{
    pthread_mutex_lock(&info->simul_mtx);
    if (info->simul_flag)
    {
        pthread_mutex_unlock(&info->simul_mtx);
        return (1);
    }
    pthread_mutex_unlock(&info->simul_mtx);
    return (0);
}

int	check_death(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_lock(&info->philos[i].time_mtx);
		if (info->philos[i].last_meal_time &&
		get_timestamp() - info->philos[i].last_meal_time >= info->time_to_die)
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
	while (!is_dead(info))
	{
        if (check_death(info))
            break ;
		ft_usleep(1, NULL);
	}
}