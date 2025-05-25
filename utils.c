/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:42:25 by skayed            #+#    #+#             */
/*   Updated: 2025/05/25 21:43:10 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	time_stamp(struct timeval start_time)
{
	struct timeval	now;
	long			seconds;
	long			microseconds;

	gettimeofday(&now, NULL);
	seconds = (now.tv_sec - start_time.tv_sec) * 1000L;
	microseconds = (now.tv_usec - start_time.tv_usec) / 1000L;
	return (seconds + microseconds);
}

void	print_state(t_philo *philo, char *msg)
{
	t_table	*table;
	long	time_since_start;

	table = philo->table;
	pthread_mutex_lock(table->print_lock);
	if (!table->is_dead)
	{
		time_since_start = time_stamp(table->start_time);
		printf("%ld %d %s", time_since_start, philo->id, msg);
	}
	pthread_mutex_unlock(table->print_lock);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork\n");
	usleep(philo->table->time_to_die * 1000);
	pthread_mutex_unlock(philo->left);
	return ;
}

void	destroy_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
	mutex = NULL;
}
