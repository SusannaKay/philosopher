#include "philosopher.h"

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		if (check_death(philo))
			return(NULL);
		if(philo->table->n_philo == 1)
		{
			pthread_mutex_lock(philo->left);
			print_state(philo, "has taken a fork\n");
			usleep(philo->table->time_to_die *1000);
			pthread_mutex_unlock(philo->left);
			return (NULL);
		}
		while(philo->meals_eaten < philo->table->meals_count)
		{
			if (philo->id % 2 == 0)
				is_eating_odd(philo);
			else if (philo->id %2 !=0)
				is_eating_uneven(philo);
			print_state(philo, "is sleeping");
			usleep(philo->table->time_to_sleep * 1000);
			print_state(philo, "is thinking\n");
		}
		
	}

}