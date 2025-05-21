/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:53 by skayed            #+#    #+#             */
/*   Updated: 2025/05/21 13:15:31 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i]->left = &table->forks[i];
		table->philos[i]->right = &table->forks[(i + 1) % table->n_philo];
		i++;
	}
	return (0);
}

static int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, routine,
				table->philos[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
			return (-1);
		table->philos[i]->id = i + 1;
		table->philos[i]->meals_eaten = 0;
		table->philos[i]->last_meal = 0;
		table->philos[i]->table = table;
		table->philos[i]->is_thinking = 0;
		i++;
	}
	if (assign_forks(table) == -1)
		return (-1);
	if (init_threads(table) == -1)
		return (-1);
	if (pthread_create(&table->monitor, NULL, monitor_philo, table) != 0)
		return (-1);
	if (pthread_join(table->monitor, NULL) != 0)
		return (-1);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philos[i]->thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
