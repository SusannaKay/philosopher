/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:14:44 by skayed            #+#    #+#             */
/*   Updated: 2025/05/24 08:20:03 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	is_eating_odd(t_philo *philo)
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
	if (philo->meals_eaten == philo->table->meals_count)
	{
		pthread_mutex_lock(philo->table->meals_lock);
		philo->table->all_eaten++;
		pthread_mutex_unlock(philo->table->meals_lock);
	}
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	usleep(200);
}
void	is_eating_uneven(t_philo *philo)
{
	usleep(1000);
	pthread_mutex_lock(philo->right);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->table->meals_lock);
	philo->last_meal = time_stamp(philo->table->start_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->table->meals_lock);
	print_state(philo, "is eating\n");
	if (philo->meals_eaten == philo->table->meals_count)
	{
		pthread_mutex_lock(philo->table->meals_lock);
		philo->table->all_eaten++;
		pthread_mutex_unlock(philo->table->meals_lock);
	}
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
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
		pthread_mutex_lock(table->meals_lock);
		if (table->all_eaten == table->meals_count)
		{
			pthread_mutex_unlock(table->meals_lock);
			return (NULL);
		}
		pthread_mutex_unlock(table->meals_lock);
		while (i < table->n_philo)
		{
			pthread_mutex_lock(table->meals_lock);
			time_since_meal = time_stamp(table->start_time)
				- table->philos[i]->last_meal;
			pthread_mutex_unlock(table->meals_lock);
			if (time_since_meal > table->time_to_die)
				return (stop_simulation(table, i), NULL);
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
	philo->last_meal = time_stamp(philo->table->start_time);
	while (1)
	{
		if (philo->table->n_philo == 1)
		{
			pthread_mutex_lock(philo->left);
			print_state(philo, "has taken a fork\n");
			usleep(philo->table->time_to_die * 1000);
			pthread_mutex_unlock(philo->left);
			return (NULL);
		}
		while ((philo->meals_eaten < philo->table->meals_count)
			|| philo->table->meals_count == -1)
		{
			if (check_death(philo))
				return (NULL);
			if (philo->id % 2 == 0 && philo->is_thinking == 1)
				is_eating_odd(philo);
			else if (philo->id % 2 != 0)
				is_eating_uneven(philo);
			print_state(philo, "is sleeping\n");
			usleep(philo->table->time_to_sleep * 1000);
			print_state(philo, "is thinking\n");
			philo->is_thinking = 1;
		}
		pthread_mutex_lock(philo->table->meals_lock);
		if (philo->meals_eaten == philo->table->meals_count)
		{
			pthread_mutex_unlock(philo->table->meals_lock);
			return (NULL);
		}
		pthread_mutex_unlock(philo->table->meals_lock);
	}
}
