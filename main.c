#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
}				t_philo;

void	*routine(void *arg)
{
	int	id;

	id = *(int *)arg;
	printf("Thread #%d è partito!\n", id);
	return (NULL);
}

int	main(void)
{
	t_philo	**philos;
	int		i;
	int		n;

	i = 0;
	n = 2;
	// Allochiamo l'array di puntatori
	philos = malloc(sizeof(t_philo *) * n);
	// Per ogni filosofo, allochiamo la struct e inizializziamo i campi
	while (i < n)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->id = i + 1;
		// STAMPE DI DEBUG
		printf("philos[%d]             = %p\n", i, (void *)philos[i]);
		printf("philos[%d]->thread     = %p (valore non inizializzato)\n", i,
				(void *)philos[i]->thread);
		printf("&philos[%d]->thread    = %p (da passare a pthread_create)\n", i,
				(void *)&philos[i]->thread);
		// Passiamo l'indirizzo del thread alla funzione
		pthread_create(&philos[i]->thread, NULL, routine, &philos[i]->id);
		i++;
	}
	// Join per evitare che il main finisca prima
	i = 0;
	while (i < n)
	{
		pthread_join(philos[i]->thread, NULL);
		free(philos[i]);
		i++;
	}
	free(philos);
	return (0);
}
