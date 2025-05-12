/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:24:09 by skayed            #+#    #+#             */
/*   Updated: 2025/05/12 18:21:29 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_all(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
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
	init_table(table, argv);
	if (!table)
		return (free_all(table), 0);
	init_philo(table);
	if (pthread_create(&table->monitor, NULL, monitor_philo, table) != 0)
		return (free_all(table), 0);
	pthread_join(table->monitor, NULL);
	return (0);
}

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="log.txt"
