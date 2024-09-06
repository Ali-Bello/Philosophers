/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:25:58 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/06 17:35:18 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <stdatomic.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define YELLOW "\x1b[33m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"

typedef struct t_info
{
    int				num_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				num_of_meals;
    int				simul_flag;
    size_t    		start_time;
    size_t    		timestamp;
    struct t_philo  *philos;
    pthread_mutex_t status_mtx;
    pthread_mutex_t simul_mtx;
} t_info;

typedef struct t_fork
{
    pthread_mutex_t mtx;
    atomic_int				status;
} t_fork;

typedef struct t_philo
{
    t_info      *info;
    struct t_philo *neighboor;
    t_fork		fork;
    pthread_t   ptid;
    int         id;
    int         meals_eaten;
    size_t		last_meal_time;
} t_philo;


int     check_input(int ac, char **av, t_info *info);
void    eat(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    think(t_philo *philo);
long    get_timestamp();
void    azrael(t_info *info);
#endif