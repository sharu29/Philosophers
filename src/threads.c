/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:50 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/27 13:33:00 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Creates the threads

int	thread_create(t_simulation *sim, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, sim->philos) != 0)
		cleanup("Thread creation error", sim, forks);
	i = 0;
	while (i < sim->philos[0].num_of_philos)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, &philo_routine,
				&sim->philos[i]) != 0)
			cleanup("Thread creation error", sim, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		cleanup("Thread join error", sim, forks);
	while (i < sim->philos[0].num_of_philos)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
			cleanup("Thread join error", sim, forks);
		i++;
	}
	return (0);
}

// if value of dead flag changed

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

// Thread routine

void	*philo_routine(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if ((p->id % 2 == 0) && p->num_of_philos > 1)
		ft_usleep(p->time_to_eat / 2);
	while (!dead_loop(p))
	{
		eat(p);
		if (dead_loop(p))
			break ;
		print_message("is sleeping", p, p->id);
		ft_usleep(p->time_to_sleep);
		print_message("is thinking", p, p->id);
		ft_usleep(1);
	}
	return (ptr);
}
