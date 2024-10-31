/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:59:14 by codespace         #+#    #+#             */
/*   Updated: 2024/10/27 04:59:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
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
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	struct t_philo	*philos;
	sem_t			*forks;
	sem_t			*max_philos;
	sem_t			*write_sem;
}					t_info;

typedef struct t_philo
{
	t_info			*info;
	pid_t			pid;
	pthread_t		death_tid;
	time_t			last_meal_time;
	int				death_flag;
	int				id;
	int				meals_eaten;
	sem_t			*time_lock;
	sem_t			*death_sem;
}					t_philo;

void				ft_usleep(size_t usec, t_philo *philo);
int					check_input(int ac, char **av, t_info *info);
void				print_error(void);
int					activity(t_philo *philo);
void				print_logs(t_info *info, int id, char *s);
time_t				get_timestamp(void);
void				*death_check(void *arg);
void				table_monitor(t_info *info);
char				*ft_itoa(int n);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
int					init_philo_sem(t_philo *philo);
int					init_sem(t_info *info);
void				ft_clean(t_info *info);
int					is_dead(t_philo *philo);
void				clean_child(t_philo *philo);
#endif