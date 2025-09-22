/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:04:07 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/19 18:16:03 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_routine(t_data *data)
{
	int			i;
	int			j;
	pthread_t	monitor;

	i = 0;
	j = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				(void *)&data->philos[i]) != 0)
			free_error(data, "Error with the thread creation");
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		free_error(data, "Error with the thread creation");
	while (j < data->num_of_philos)
	{
		pthread_join(data->philos[j].thread, NULL);
		j++;
	}
	pthread_join(monitor, NULL);
	return ;
}

bool	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->dead_lock);
		// perror("TRUE ");
		// printf("id: %d\n", philo->id);
		return (true);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

void	*philo_routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (!check_dead(philo))
	{
		if (eat(philo))
			break ;
		if (nap(philo))
			break ;
		if (check_dead(philo))
			break ;
		usleep(100);
	}
	return (NULL);
}

void	*monitor_routine(void *input)
{
	t_data	*data;

	data = (t_data *)input;
	printf("data->dead_flag: %d\n", data->dead_flag);
	while (1)
	{
		printf("data->dead_flag: %d\n", data->dead_flag);
		if (is_philo_dead(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = true;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		if (data->num_times_to_eat != -1 && have_philos_finish(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = true;
			pthread_mutex_unlock(&data->dead_lock);
			printf("All the philo have eaten. Simulation is finished\n");
			return (NULL);
		}
		usleep(100);
	}
}

bool	is_philo_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if ((get_current_time()
				- data->philos[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_lock);
			print_status(&data->philos[i], "died");
			return (true);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (false);
}

bool	have_philos_finish(t_data *data)
{
	int		i;
	bool	flag_all_eaten;

	i = 0;
	flag_all_eaten = true;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten < data->num_times_to_eat)
		{
			flag_all_eaten = false;
			pthread_mutex_unlock(&data->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (flag_all_eaten);
}
