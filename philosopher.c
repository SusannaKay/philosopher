/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:24:09 by skayed            #+#    #+#             */
/*   Updated: 2025/05/06 12:29:39 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_all(t_table *table)
{
	if (table->philo)
	{
		free(table->philo);
		table->philo = NULL;
	}
	free(table);
}


int	main(int argc, char *argv[])
{
	t_table *table;

	if (argc < 5)
		return(printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep
		[number_of_times_each_philosopher_must_eat]", 0));
	table = init_table(table, argv);
	if (!table)
		return(free_all(table), 0);

}