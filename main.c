/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:34 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/05/05 17:05:14 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (ft_error("Invalid number of arguments"));
	if (check_args(&data, argc, argv))
		return (1);
	init_data(&data);
	if (dinner(&data))
		return (1);
	clean(&data, NULL);
}
