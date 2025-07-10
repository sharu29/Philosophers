/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:03 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/13 20:19:16 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if the argument is a valid positive number

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

// validate user input

int	validate_input(char **args)
{
	if (is_valid_number(args[1]) == 1 || ft_atoi(args[1]) <= 0
		|| ft_atoi(args[1]) > PHILO_MAX)
		return (printf("Invalid number of philosophers\n"), 1);
	if (is_valid_number(args[2]) == 1 || ft_atoi(args[2]) <= 0)
		return (printf("Invalid time to die\n"), 1);
	if (is_valid_number(args[3]) == 1 || ft_atoi(args[3]) <= 0)
		return (printf("Invalid time to eat\n"), 1);
	if (is_valid_number(args[4]) == 1 || ft_atoi(args[4]) <= 0)
		return (printf("Invalid time to sleep\n"), 1);
	if (args[5] && (is_valid_number(args[5]) == 1 || ft_atoi(args[5]) < 0))
		return (printf("Invalid meal limit\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_simulation	sim;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (validate_input(av) == 1)
		return (1);
	init_program(&sim, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &sim, forks, av);
	thread_create(&sim, forks);
	cleanup(NULL, &sim, forks);
	return (0);
}
