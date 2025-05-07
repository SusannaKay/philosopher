/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:16:16 by skayed            #+#    #+#             */
/*   Updated: 2025/05/07 10:49:56 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>   //memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   //usleep

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int					n_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					meals_count;
	int					is_dead;
	struct timeval		start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
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

t_table					*init_table(t_table *table, char *argv[]);
void					init_philo(t_table *table);
void					free_all(t_table *table);
void					*routine(void *arg);

#endif