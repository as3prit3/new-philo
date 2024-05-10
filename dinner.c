/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:03:51 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/09 17:09:05 by hhadhadi         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
	while (++i < data->nb_philo)
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]))
			return (clean(data, "Thread creation failed"));
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
