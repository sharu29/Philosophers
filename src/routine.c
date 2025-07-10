/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:24 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/27 13:33:25 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Think

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

// Dream

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

// Eat

static void	lock_forks(t_philo *p, pthread_mutex_t **a, pthread_mutex_t **b)
{
	if (p->l_fork < p->r_fork)
	{
		*a = p->l_fork;
		*b = p->r_fork;
	}
	else
	{
		*a = p->r_fork;
		*b = p->l_fork;
	}
	pthread_mutex_lock(*a);
	print_message("has taken a fork", p, p->id);
	if (p->num_of_philos == 1)
	{
		ft_usleep(p->time_to_die);
		pthread_mutex_unlock(*a);
		return ;
	}
	pthread_mutex_lock(*b);
	print_message("has taken a fork", p, p->id);
}

void	eat(t_philo *p)
{
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;

	lock_forks(p, &f1, &f2);
	if (p->num_of_philos == 1)
		return ;
	pthread_mutex_lock(p->meal_lock);
	p->last_meal = get_current_time();
	pthread_mutex_unlock(p->meal_lock);
	print_message("is eating", p, p->id);
	ft_usleep(p->time_to_eat);
	pthread_mutex_lock(p->meal_lock);
	p->meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	pthread_mutex_unlock(f2);
	pthread_mutex_unlock(f1);
}

void	stagger_even_start(t_philo *p)
{
	if (p->num_of_philos > 1 && (p->id % 2 == 0))
		ft_usleep(p->time_to_eat / 2);
}
