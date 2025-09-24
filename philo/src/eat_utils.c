/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:38:58 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/24 12:21:34 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	pthread_mutex_lock(first_fork);
	if (print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(first_fork), 1);
	pthread_mutex_lock(second_fork);
	if (print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	return (0);
}

int	do_eat(t_philo *philo)
{
	if (print_status(philo, "is eating"))
	{
		// if (philo->id % 2 == 0)
		// {
		// 	pthread_mutex_unlock(philo->r_fork);
		// 	pthread_mutex_unlock(philo->l_fork);
		// }
		// else
		// {
		// 	pthread_mutex_unlock(philo->l_fork);
		// 	pthread_mutex_unlock(philo->r_fork);
		// }
		return (1);
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep(1000 * philo->time_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	return (0);
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
