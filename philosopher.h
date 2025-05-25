/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:16:16 by skayed            #+#    #+#             */
/*   Updated: 2025/05/25 21:43:24 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int					n_philo;
	int					all_eaten;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					meals_count;
	int					is_dead;
	struct timeval		start_time;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*death_mutex;
	pthread_mutex_t		*meals_lock;
	t_philo				**philos;

}						t_table;
typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	t_table				*table;

}						t_philo;

int						init_table(t_table *table, char *argv[]);
int						init_philo(t_table *table);
void					free_all(t_table *table);
void					*routine(void *arg);
void					print_state(t_philo *philo, char *msg);
long					time_stamp(struct timeval start_time);
void					*monitor_philo(void *arg);
void					stop_simulation(t_table *table, int i);
int						check_death(t_philo *philo);
void					free_philo(t_table *table);
int						ft_isdigit(char c);
void					one_philo(t_philo *philo);
void					destroy_mutex(pthread_mutex_t *mutex);
#endif
