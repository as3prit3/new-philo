/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:30:39 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/07 14:54:55 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

long	ft_atol(char *str)
{
	long	number;

	number = 0;
	if (!*str)
		return (0);
	while (*str && *str == ' ')
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
		number = number * 10 + *str++ - 48;
	if (*str)
		return (0);
	return (number);
}

int	ft_usleep(long time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
}

int	clean(t_data *data, char *str)
{
	int	i;

	i = -1;
	if (str)
		printf("%s\n", str);
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	return (1);
}
