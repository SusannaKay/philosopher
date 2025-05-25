/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:24:09 by skayed            #+#    #+#             */
/*   Updated: 2025/05/25 20:33:26 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Error: Invalid number of args\n"), 1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("Error: malloc failed\n"), 1);
	if (init_table(table, argv) == -1)
	{
		printf("Error: init table failed\n");
		return (free_all(table), -1);
	}
	if (init_philo(table) == -1)
	{
		printf("Error: init philo failed\n");
		return (free_all(table), -1);
	}
	free_all(table);
	return (0);
}
