/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:41:01 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/10 16:35:37 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	check_args(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atol(argv[1]);
	if (data->nb_philo <= 0 || data->nb_philo > MAX_PHILO)
		return (ft_error("Invalide number of philos"));
	data->time_to_die = ft_atol(argv[2]);
	if (data->time_to_die <= 0)
		return (ft_error("Invalide time_to_die"));
	data->time_to_eat = ft_atol(argv[3]);
	if (data->time_to_eat <= 0)
		return (ft_error("Invalide time_to_eat"));
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_sleep <= 0)
		return (ft_error("Invalide time_to_sleep"));
	data->nb_of_time_to_eat = -1;
	if (argc == 6)
	{
		data->nb_of_time_to_eat = ft_atol(argv[5]);
		if (data->nb_of_time_to_eat <= 0)
			return (ft_error("Invalide nb_of_time_to_eat"));
	}
	return (0);
}

// void	set_start_simulation(t_data *data)
// {
// 	pthread_mutex_lock(&(data->start_mutex));
// 	data->start_simulation = true;
// 	pthread_mutex_unlock(&(data->start_mutex));
// }

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].nb_of_meals = 0;
		data->philos[i].last_time_eaten = data->start_time;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i + 1];
		if (i == data->nb_philo - 1)
		{
			data->philos[i].l_fork = &data->forks[0];
			data->philos[i].r_fork = &data->forks[i];
		}
	}
}
	// data->philos[i].l_fork = &data->forks[i];
	// if (i == 0)
	// 	data->philos[i].r_fork = &data->forks[data->nb_philo - 1];
	// else
	// 	data->philos[i].r_fork = &data->forks[i - 1];
//-----------
	// data->philos[i].r_fork = &(data->forks[i]);
	// if (i != 0)
	// 	data->philos[i].l_fork = &(data->forks[i - 1]);
	// if (data->nb_philo != 1)
	// 	data->philos[0].l_fork = &(data->forks[data->nb_philo - 1]);
	// else
	// 	data->philos[0].l_fork = &(data->forks[0]);
//-----------
	// if (data->philos[i].id % 2 == 1)
	// {
	// 	data->philos[i].l_fork = &data->forks[0];
	// 	data->philos[i].r_fork = &data->forks[i];
	// }

static void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	init_data(t_data *data)
{
	data->start_time = get_time();
	data->end_simulation = false;
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
	init_forks(data);
	init_philos(data);
}
