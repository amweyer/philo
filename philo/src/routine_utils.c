/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:52:29 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/24 11:59:30 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
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
	if (check_dead(philo))
		return (1);
	return (0);
}

int	thinking(t_philo *philo)
{
	int	time2think;

	if (check_dead(philo))
		return (1);
	time2think = (philo->time_to_die - philo->time_to_eat
			- philo->time_to_sleep) / 2;
	if (print_status(philo, "is thinking"))
		return (1);
	usleep(time2think * 1000);
	return (0);
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

// int	myusleep(t_philo *philo, int time)
// {
// 	int	i;

// 	i = 0;
// 	while (i < time)
// 	{
// 		if (check_dead(philo))
// 			return (1);
// 		i = i + 50;
// 		usleep(50);
// 	}
// 	return(0);
// }
