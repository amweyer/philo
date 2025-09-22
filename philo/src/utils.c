/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:33:27 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/05 18:09:07 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *arg)
{
	int i;
	long nb;

	i = 0;
	nb = 0;
	if (!arg)
		return (-1);
	while (arg[i] == ' ' || (arg[i] > 8 && arg[i] < 14))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			return (-1);
		i++;
	}
	while (arg[i] && (arg[i] >= '0' && arg[i] <= '9'))
	{
		nb = nb * 10 + (arg[i] - '0');
		if (nb > INT_MAX)
			return (-1);
		i++;
	}
	if (arg[i] != '\0')
		return (-1);
	return ((int)nb);
}


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("error\n gettimeofday()\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		exit_error("Failed initialising mutex");
}