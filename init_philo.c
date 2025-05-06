/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:53 by skayed            #+#    #+#             */
/*   Updated: 2025/05/06 12:35:55 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *s)
{
	int	i;

	i = *(int *)s;
	printf("thread %d is printing\n", i);
	sleep(3);
	printf("thread %d is ended\n", i);
	return (NULL);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(table->n_philo * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (free_all(table));
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(table->forks[i], NULL) != 0)
			return(free_all(table));
	}
}

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
			return (free_all(table));
		if (pthread_create(&table->*philos[i]->thread, NULL, routine,
				NULL) != 0)
			return (free_all(table));
		table->philo[i]->id = i + 1;
		table->philo[i]->meals_eaten = 0;
		i++;
	}
	while (i < table->n_philo)
	{
		if (pthread_join(table->*philos[i]->thread, NULL) != 0)
			return (free_all(table));
		i++;
	}
	return ;
}
