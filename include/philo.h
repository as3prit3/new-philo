/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:16:21 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/05 22:45:57 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdio.h>

#define MAX_PHILO 300

typedef struct s_data	t_data;

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				nb_of_meals;
	long			last_time_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	
}			t_philo;

typedef struct	s_data
{
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_t		monitor;
	int				nb_philo;
	int				nb_of_time_to_eat;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	bool			end_simulation;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	end_mutex;
}			t_data;

int		ft_error(char *str);
long	ft_atol(char *str);
long	get_time(void);

int		check_args(t_data *data, int argc, char **argv);
void	init_data(t_data *data);
int		dinner(t_data *data);
bool	check_if_simulation_ended(t_data *data);
void	*monitoring(void *arg);

void	print_message(t_philo *philo, int id, char *str);
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo * philo);

int		clean(t_data *data, char *str);
#endif