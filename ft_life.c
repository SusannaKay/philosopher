/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:14:44 by skayed            #+#    #+#             */
/*   Updated: 2025/05/12 18:42:15 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->table->death_mutex);
	dead = philo->table->is_dead;
	pthread_mutex_unlock(philo->table->death_mutex);
	return (dead);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->table->meals_lock);
	philo->last_meal = time_stamp(philo->table->start_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->table->meals_lock);
	print_state(philo, "is eating\n");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
void	*monitor_philo(void *arg)
{
	t_table	*table;
	int		i;
	long	time_since_meal;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_lock(table->meals_lock);
			time_since_meal = time_stamp(table->start_time) - table->philos[i]->last_meal;
			pthread_mutex_unlock(table->meals_lock);
			if (time_since_meal > table->time_to_die)
			{
				pthread_mutex_lock(table->print_lock);
				pthread_mutex_lock(table->death_mutex);
				if (table->is_dead == 0)
				{
					table->is_dead = 1;
					printf("%ld %d died\n", time_stamp(table->start_time), table->philos[i]->id);
				}
				pthread_mutex_unlock(table->death_mutex);
				pthread_mutex_unlock(table->print_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;	
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		is_eating(philo);
		print_state(philo, "is sleeping\n");
		usleep(philo->table->time_to_sleep * 1000);
		print_state(philo, "is thinking\n");
	}
}
