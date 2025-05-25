/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:36 by skayed            #+#    #+#             */
/*   Updated: 2025/05/25 20:06:09 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

static int	init_mutex(t_table *table)
{
	table->forks = malloc(table->n_philo * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (0);
	table->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->death_mutex)
		return (0);
	if (pthread_mutex_init(table->death_mutex, NULL) != 0)
		return (0);
	table->meals_lock = malloc(sizeof(pthread_mutex_t));
	if (!table->meals_lock)
		return (0);
	if (pthread_mutex_init(table->meals_lock, NULL) != 0)
		return (0);
	table->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!table->print_lock)
		return (0);
	if (pthread_mutex_init(table->print_lock, NULL) != 0)
		return (0);
	return (1);
}

static int	check_args(t_table *table)
{
	if (table->n_philo < 0)
		return (-1);
	if (table->time_to_die < 0)
		return (-1);
	if (table->time_to_eat < 0)
		return (-1);
	if (table->time_to_sleep < 0)
		return (-1);
	return (0);
}

int	init_table(t_table *table, char *argv[])
{
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (check_args(table) < 0)
		return (-1);
	if (argv[5])
	{
		table->meals_count = ft_atoi(argv[5]);
		if (table->meals_count < 0)
			return (-1);
	}
	else
		table->meals_count = -1;
	gettimeofday(&table->start_time, NULL);
	table->is_dead = 0;
	table->all_eaten = 0;
	table->philos = malloc(table->n_philo * sizeof(t_philo *));
	if (!table->philos)
		return (-1);
	if (!init_mutex(table))
		return (-1);
	return (0);
}
