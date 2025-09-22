/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:52:29 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/22 19:37:07 by amweyer          ###   ########.fr       */
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
		return (1);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep(1000 * philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

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
	print_status(philo, "is sleeping");
	if (philo->time_to_eat > philo->time_to_sleep)
		usleep(1000 * philo->time_to_eat + 100);
	else
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
