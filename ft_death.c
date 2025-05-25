/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:41:57 by skayed            #+#    #+#             */
/*   Updated: 2025/05/25 21:43:00 by skayed           ###   ########.fr       */
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

void	stop_simulation(t_table *table, int i)
{
	pthread_mutex_lock(table->print_lock);
	pthread_mutex_lock(table->death_mutex);
	if (table->is_dead == 0)
	{
		table->is_dead = 1;
		printf("%ld %d died\n", time_stamp(table->start_time),
			table->philos[i]->id);
	}
	pthread_mutex_unlock(table->death_mutex);
	pthread_mutex_unlock(table->print_lock);
	return ;
}

void	free_mutex(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	if (table->forks)
	{
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	if (table->print_lock)
		destroy_mutex(table->print_lock);
	if (table->death_mutex)
		destroy_mutex(table->death_mutex);
	if (table->meals_lock)
		destroy_mutex(table->meals_lock);
}

void	free_philo(t_table *table)
{
	int	i;

	if (!table || !table->philos)
		return ;
	i = 0;
	while (i < table->n_philo)
	{
		if (table->philos[i])
		{
			free(table->philos[i]);
			table->philos[i] = NULL;
		}
		i++;
	}
	free(table->philos);
	table->philos = NULL;
}

void	free_all(t_table *table)
{
	if (!table)
		return ;
	free_mutex(table);
	free_philo(table);
	free(table);
}
