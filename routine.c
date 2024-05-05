/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:21:07 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/05 22:39:46 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	print_message(t_philo *philo, int id, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_mutex);
	time = get_time() - philo->data->start_time;
	if (!check_if_simulation_ended(philo->data))
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->write_mutex);	
}

void	think(t_philo *philo)
{
	print_message(philo, philo->id, "is thinking");
}

void	dream(t_philo *philo)
{
	print_message(philo, philo->id, "is sleeping");
	usleep(philo->data->time_to_sleep * 1e3);
}

void	eat(t_philo * philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, philo->id, "has taken a fork");
	if (philo->data->nb_philo == 1)
	{
		usleep(philo->data->time_to_die * 1e3);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, philo->id, "has taken a fork");
	print_message(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->nb_of_meals++;
	philo->last_time_eaten = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	usleep(philo->data->time_to_eat * 1e3);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
