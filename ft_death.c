/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:41:57 by skayed            #+#    #+#             */
/*   Updated: 2025/05/15 10:47:51 by skayed           ###   ########.fr       */
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

void stop_simulation(t_table *table, int i)
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
				return;
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	pthread_mutex_destroy(table->forks);
	pthread_mutex_destroy(table->print_lock);
	pthread_mutex_destroy(table->death_mutex);
	pthread_mutex_destroy(table->meals_lock);
	if (table->philos)
	{
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(table->philos[i]->left);
			pthread_mutex_destroy(table->philos[i]->right);
			table->philos[i]->table = NULL;
			free(table->philos[i]);
			i++;
		}
	}
	free(table);
}