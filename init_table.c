/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:36 by skayed            #+#    #+#             */
/*   Updated: 2025/05/06 12:31:39 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '-')
		return (printf("Error: Numbers must be positive."), -1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (printf("Error: Input must be a number."), -1);
		result = result * 10 + (*str - 48);
		str++;
	}
	if (result > 2147483647)
		return (printf("Error: Input must be below INT_MAX."), -1);
	if (result == 0)
		return (printf("Error: Input must be > 0"), -1);
	return (result);
}

t_table	*init_table(t_table *table, char *argv[])
{
	if ((table->n_philo = ft_atoi(argv[1])) > 200
		|| table->n_philo = ft_atoi(argv[1]) < 0)
		return (NULL);
	if ((table->time_to_die = ft_atoi(argv[2])) < 0)
		return (NULL);
	if ((table->time_to_eat = ft_atoi(argv[3])) < 0)
		return (NULL);
	if ((table->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (NULL);
	if (argv[5])
	{
		if ((table->meals_count = ft_atoi(argv[5])) < 0)
			return (NULL);
	}
	gettimeofday(&table->start_time, NULL);
	table->is_dead = 0;
	table->philos = malloc(table->n_philo * sizeof(t_philo *));
	if (!table->philos)
		return (free_all(table));
	return (table);
}


