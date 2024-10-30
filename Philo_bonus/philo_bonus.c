/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:59:11 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 14:51:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clean(t_info *info)
{
	if (info->philos)
		free(info->philos);
	memset(info, 0, sizeof(t_info));
}

int	init_objects(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->num_of_philos);
	info->forks = malloc(sizeof(sem_t) * info->num_of_philos);
	if (!info->philos || !info->forks)
		return (ft_clean(info), 1);
	i = 0;
	while (i < info->num_of_philos)
	{
		memset(&info->philos[i], 0, sizeof(t_philo));
		if (init_time_sem(&info->philos[i]))
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
		ft_usleep(1);
		i++;
	}
	i = 0;
	table_monitor(&info);
	ft_clean(&info);
	return (0);
}
