/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:25:58 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/01 07:06:59 by aderraj          ###   ########.fr       */
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


typedef struct t_info
{
    int				simulation_flag;
    int				num_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				num_of_meals;
    int				death_flag;
    long    		start_time;
    long    		timestamp;
    struct t_philo	*philos;
    pthread_mutex_t	*forks;
    pthread_mutex_t	time_mutex;
} t_info;

typedef struct t_fork
{
    int state;
    pthread_mutex_t mutex;
} t_fork;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING
} e_status;

typedef struct t_philo
{
    t_info      *info;
    pthread_t   ptid;
    int         philo_no;
    int         meal_no;
    long		last_meal;
    pthread_mutex_t status_mutex;
    e_status status;
} t_philo;


int     check_input(int ac, char **av, t_info *info);
void    eat(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    think(t_philo *philo);
long    get_timestamp();
#endif