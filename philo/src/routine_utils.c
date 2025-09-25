/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:52:29 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/24 21:43:32 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	if (take_forks(philo))
		return (1);
	if (check_dead(philo))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
		}
		return (1);
	}
	if (do_eat(philo))
		return (1);
	return (0);
}

int	nap(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	if (print_status(philo, "is sleeping"))
		return (1);
	usleep(1000 * philo->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	// int	time2think;

	if (check_dead(philo))
		return (1);
	// time2think = (philo->time_to_die - philo->time_to_eat
	// 		- philo->time_to_sleep) / 2;
	if (print_status(philo, "is thinking"))
		return (1);
	// if (time2think < 0)
	// time2think = 60;
	
	// usleep(5000);
	return (0);
}

int	is_philo_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		// (data->philos[i].last_meal != 0 && (data->time_to_eat < data->time_to_die)) && 
		// pthread_mutex_lock(&data->write_lock);
		// printf("last meal = %zu | current time = %lu\n", data->philos[i].last_meal, get_current_time());
		// pthread_mutex_unlock(&data->write_lock);

		if ((get_current_time()
				- data->philos[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = true;
			pthread_mutex_lock(&data->write_lock);
			printf("%ld %d %s\n", get_current_time(), data->philos[i].id,
				"died");
			pthread_mutex_unlock(&data->write_lock);
			pthread_mutex_unlock(&data->dead_lock);
			return (true);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (false);
}

int	myusleep(t_philo *philo, unsigned long time)
{
	// size_t	first_time;

	// time;
	// first_time = get_current_time();
	// printf(" first time = %zu\n", first_time);
	while (1)
	{
		// pthread_mutex_lock(philo->write_lock);
		//printf("firsttime = %zu | current time = %lu\n", first_time, get_current_time());
		// printf(" time = %lu\n", get_current_time());
		// pthread_mutex_unlock(philo->write_lock);
		// sleep(3);
		if (check_dead(philo))
			return (1);
		if (get_current_time() >= time)
			break;
		usleep(50);
	}
	return (0);
}
