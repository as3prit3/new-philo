/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:03:51 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/07 18:52:53 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	check_if_simulation_ended(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_simulation == true)
		return (pthread_mutex_unlock(&data->end_mutex), true);
	pthread_mutex_unlock(&data->end_mutex);
	return (false);
}


// static bool	check_start_simulation(t_data *data)
// {
// 	bool	status = false;

// 	pthread_mutex_lock(&(data->start_mutex));
// 	status = data->start_simulation;
// 	pthread_mutex_unlock(&(data->start_mutex));
// 	return (status);
// }

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	// while (check_start_simulation(philo->data) == false)
	// 	;
	if (philo->id % 2 == 0)
		ft_usleep(15);
	while (!check_if_simulation_ended(philo->data))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}

int	dinner(t_data *data)
{
	int	i;

	i = -1;
	// data->start_time = get_time();
	while (++i < data->nb_philo)
	{
		// data->philos[i].last_time_eaten = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]))
			return (clean(data, "Thread creation failed"));
	}
	if (pthread_create(&data->monitor, NULL, monitoring,
			data->philos))
			return (clean(data, "Thread creation failed"));
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philos[i].thread, NULL))
			return (clean(data, "Thread join failed"));
	if (pthread_join(data->monitor, NULL))
		return (clean(data, "Thread join failed"));
	return (0);
}
