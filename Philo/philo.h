/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:25:58 by aderraj           #+#    #+#             */
/*   Updated: 2024/10/08 23:34:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define YELLOW "\x1b[33m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"
# define ITALIC "\x1b[3m"
# define UNDERLINE "\x1b[4m"

typedef struct t_info
{
	int				num_of_philos;
	int				num_of_meals;
	int				simul_flag;
	int				meals_flag;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	struct t_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals_mtx;
	pthread_mutex_t	simul_mtx;
	pthread_mutex_t	print_mtx;
}					t_info;

typedef struct t_philo
{
	t_info			*info;
	pthread_t		ptid;
	int				id;
	int				meals_eaten;
	time_t			last_meal_time;
	pthread_mutex_t	time_mtx;
}					t_philo;

time_t				get_timestamp(void);
int					check_input(int ac, char **av, t_info *info);
int					is_dead(t_info *info);
int					meals_check(t_info *info);
void				eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				monitor(t_info *info);
void				print_logs(t_info *info, int id, char *s);
void				print_error(void);
void				ft_usleep(size_t usec, t_philo *philo);
void				release_forks(t_philo *philo);
#endif