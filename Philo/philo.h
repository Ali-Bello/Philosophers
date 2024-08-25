/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:25:58 by aderraj           #+#    #+#             */
/*   Updated: 2024/08/25 18:14:34 by aderraj          ###   ########.fr       */
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

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING
} e_status;

typedef struct t_philo
{
    int philo_no;
    int time_counter;
    int meal_no;
    long start_time;
    long last_meal;
    e_status status;
} t_philo;

typedef struct t_info
{
    int simulation_flag;
    int num_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_meals;
    int death_flag;
    long    timestamp;
    t_philo     *philos;
    pthread_t   *philos_id;
    pthread_mutex_t *forks;
    pthread_mutex_t time_mutex;
} t_info;

int check_input(int ac, char **av, t_info *info);

#endif