/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:52:29 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/19 18:13:07 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep(1000 * philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	nap(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	print_status(philo, "is sleeping");
	usleep(1000 * philo->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	print_status(philo, "is thinking");
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	size_t timestamp;

	timestamp = get_current_time();
	pthread_mutex_lock(philo->write_lock);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(philo->write_lock);
}