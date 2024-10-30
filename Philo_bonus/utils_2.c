/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:40:04 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 14:49:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

time_t	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t usec)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < usec)
		usleep(100);
}

int init_time_sem(t_philo *philo)
{
    char    *str;
    char    *tmp;

    tmp = ft_itoa(philo->id);
    str = ft_strjoin("/time_sem_", tmp);
    free(tmp);
	sem_unlink(str);
	philo->time_lock = sem_open(str, O_CREAT, 0644, 1);
    if (philo->time_lock == SEM_FAILED)
        return (printf("Error : sem_open failed\n"), 1);
    sem_unlink(str);
    return (0);
}

int init_sem(t_info *info)
{
    sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, 0644, info->num_of_philos);
	if (info->forks == SEM_FAILED)
		return (printf("Error : sem_open failed\n"), 1);
	sem_unlink("/max_philos_to_eat");
	info->max_philos = sem_open("/max_philos_to_eat", O_CREAT, 0644, info->num_of_philos - 1);
	if (info->max_philos == SEM_FAILED)
		return (printf("Error : sem_open failed\n"), 1);
	sem_unlink("/write_lock");
	info->write_sem = sem_open("/write_lock", O_CREAT, 0644, 1);
	if (info->write_sem == SEM_FAILED)
		return (printf("Error : sem_open failed\n"), 1);
}
