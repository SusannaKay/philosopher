/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:14:44 by skayed            #+#    #+#             */
/*   Updated: 2025/05/08 12:16:59 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right);
	print_state(philo, "has taken a fork\n");
	print_state(philo, "is eating\n");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	print_state(philo, "is sleeping\n");
	usleep(philo->table->time_to_sleep * 1000);
	print_state(philo, "is thinking\n");
	usleep(philo->table->time_to_die * 1000);
	
	return (NULL);
}
