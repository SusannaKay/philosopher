/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:42:25 by skayed            #+#    #+#             */
/*   Updated: 2025/05/25 19:38:05 by skayed           ###   ########.fr       */
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
