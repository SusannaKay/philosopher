/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:24:09 by skayed            #+#    #+#             */
/*   Updated: 2025/05/21 15:51:47 by skayed           ###   ########.fr       */
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
		return (free_all(table), -1);
	if (init_philo(table) == -1)
		return (free_all(table), -1);
	free_all(table);
	return (0);
}

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=helgrind --log-file="log.txt"


// piu di 200 filosofi 
// data race in monitor filo 
// 