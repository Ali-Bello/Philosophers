/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:59:11 by codespace         #+#    #+#             */
/*   Updated: 2024/10/31 15:42:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clean(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		sem_close(info->philos[i].death_sem);
		sem_close(info->philos[i].time_lock);
		i++;
	}
	free(info->philos);
	if (info->forks)
		sem_close(info->forks);
	if (info->max_philos)
		sem_close(info->max_philos);
	if (info->write_sem)
		sem_close(info->write_sem);
	memset(info, 0, sizeof(t_info));
}

int	init_objects(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->num_of_philos);
	info->forks = NULL;
	if (!info->philos)
		return (ft_clean(info), 1);
	i = 0;
	while (i < info->num_of_philos)
	{
		memset(&info->philos[i], 0, sizeof(t_philo));
		if (init_philo_sem(&info->philos[i]))
			return (ft_clean(info), -1);
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		i++;
	}
	if (init_sem(info))
		return (ft_clean(info), -1);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	memset(&info, 0, sizeof(t_info));
	if (check_input(ac, av, &info) || init_objects(&info))
		return (print_error(), -1);
	i = 0;
	info.start_time = get_timestamp();
	while (i < info.num_of_philos)
	{
		info.philos[i].pid = fork();
		if (info.philos[i].pid < 0)
			return (ft_clean(&info), 0);
		else if (info.philos[i].pid == 0)
			return (activity(&info.philos[i]));
		ft_usleep(1, NULL);
		i++;
	}
	i = 0;
	table_monitor(&info);
	return (0);
}
