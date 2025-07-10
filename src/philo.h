/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:16:19 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/27 13:50:42 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_simulation
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_simulation;

// main
int					validate_input(char **args);
int					is_valid_number(char *str);

// Initialisation
void				init_input(t_philo *philo, char **av);
void				init_philos(t_philo *philos, t_simulation *sim,
						pthread_mutex_t *forks, char **av);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_program(t_simulation *sim, t_philo *philos);

// utils
int					ft_atoi(const char *ptr);
size_t				ft_strlen(const char *str);
long				get_current_time(void);
void				ft_usleep(long millisec);
void				cleanup(char *str, t_simulation *sim,
						pthread_mutex_t *forks);

// threads
int					thread_create(t_simulation *sim, pthread_mutex_t *forks);
int					dead_loop(t_philo *philo);
void				*philo_routine(void *ptr);

// monitor
int					check_if_all_ate(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
void				print_message(char *str, t_philo *philo, int id);
void				*monitor(void *ptr);

// routine
void				think(t_philo *philo);
void				dream(t_philo *philo);
void				eat(t_philo *philo);
void				stagger_even_start(t_philo *p);

#endif