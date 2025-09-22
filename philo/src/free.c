/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:04:28 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/22 16:37:54 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->philos)
			free(data->philos);
		while (i < data->num_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		pthread_mutex_destroy(&data->dead_lock);
	}
}

void	clean_error(t_data *data, char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	clean_all(data);
}
