/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:14 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/13 11:10:23 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static bool	philo_died(t_philo *philo, long time_to_die)
{
	long	curr_time;

	pthread_mutex_lock(&philo->data->meal_mutex);
	curr_time = get_time() - philo->last_time_eaten;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (curr_time >= time_to_die)
		return (true);
	return (false);
}

static bool	check_for_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].data->nb_philo)
	{
		if (philo_died(&philo[i], philo[i].data->time_to_die))
		{
			print_message(&philo[i], philo[i].id, "died");
			pthread_mutex_lock(&philo[i].data->end_mutex);
			philo[i].data->end_simulation = true;
			pthread_mutex_unlock(&philo[i].data->end_mutex);
			return (true);
		}
	}
	return (false);
}

static bool	check_meals(t_philo *philo)
{
	int	i;
	int	done_eating;

	i = -1;
	done_eating = 0;
	if (philo[0].data->nb_of_time_to_eat == -1)
		return (false);
	while (++i < philo[0].data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].data->meal_mutex);
		if (philo[i].nb_of_meals >= philo[i].data->nb_of_time_to_eat)
			done_eating++;
		pthread_mutex_unlock(&philo[i].data->meal_mutex);
	}
	if (done_eating == philo[0].data->nb_philo)
	{
		pthread_mutex_lock(&philo[0].data->end_mutex);
		philo[0].data->end_simulation = true;
		pthread_mutex_unlock(&philo[0].data->end_mutex);
		return (true);
	}
	return (false);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (check_for_death(philo) || check_meals(philo))
			break ;
	return (NULL);
}
