/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:24:09 by skayed            #+#    #+#             */
/*   Updated: 2025/05/15 10:29:52 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	main(int argc, char *argv[])
{
	t_table	*table;

	table = NULL;
	if (argc < 5)
		return (0);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (init_table(table, argv) <0 )
		return (free_all(table), 0);
	init_philo(table);
	return (0);
}

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="log.txt"
