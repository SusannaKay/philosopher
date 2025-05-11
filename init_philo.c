/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:53 by skayed            #+#    #+#             */
/*   Updated: 2025/05/11 20:34:09 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (free_all(table));
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i]->left = &table->forks[i];
		table->philos[i]->right = &table->forks[(i + 1) % table->n_philo];
		i++;
	}
}

static void	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, routine,
				table->philos[i]) != 0)
			return (free_all(table));
		i++;
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
		table->philos[i]->id = i + 1;
		table->philos[i]->meals_eaten = 0;
		table->philos[i]->table = table;
		i++;
	}
	assign_forks(table);
	init_threads(table);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philos[i]->thread, NULL) != 0)
			return (free_all(table));
		i++;
	}
	return ;
}
