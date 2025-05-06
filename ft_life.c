/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <skayed@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:14:44 by skayed            #+#    #+#             */
/*   Updated: 2025/04/30 12:54:06 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

void	is_sleep(t_table *table)
{
	if (table ->is_dead)
		return ;
	printf("%d is sleeping\n"); // malloccare array di philo 
	sleep(time_to_sleep);
}

void	is_think(void)
{
	if (is_dead)
		return ;
	printf("is thinking");
	sleep(time_to_think);
}

void is_eating()
{
	if (is_dead)
		return;
	// mutex fork 1
	// mutex fork 2
	printf("is eating");
	sleep(time_to_eat);

	//unlock mutex
	
}