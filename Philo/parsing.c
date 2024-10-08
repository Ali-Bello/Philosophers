/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:28:06 by aderraj           #+#    #+#             */
/*   Updated: 2024/10/08 21:46:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((sign * result) > INT_MAX || (sign * result) < INT_MIN)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '+' && !(str[i] >= '0' && str[i] <= '9') && !(str[i] >= 9
				&& str[i] <= 13) && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_values(t_info *info, char **av)
{
	info->num_of_philos = ft_atoi(av[1]);
	if (!info->num_of_philos || info->num_of_philos > 200)
		return (1);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (!info->time_to_die || info->time_to_die < 60 || !info->time_to_eat
		|| info->time_to_eat < 60 || !info->time_to_sleep
		|| info->time_to_sleep < 60)
		return (1);
	info->num_of_meals = ft_atoi(av[5]);
	return (0);
}

int	check_input(int ac, char **av, t_info *info)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (2);
	i = 1;
	while (av[i] && check_digit(av[i]))
		i++;
	if (i < 5 || (ac == 6 && i < 6))
		return (1);
	return (check_values(info, av));
}
