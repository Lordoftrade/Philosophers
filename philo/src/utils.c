/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/03 21:21:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

void	ft_usleep(int ms)
{
	long long	start;

	start = what_time_is_it();
	while (what_time_is_it() - start < ms)
		usleep(500);
}

void	free_data(t_data *data)
{
	int	i;

	if (data->philo)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&data->philo[i].m_last_meal);
			pthread_mutex_destroy(&data->philo[i].m_number_meals);
			i++;
		}
		free(data->philo);
	}
	if (data->m_forks)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&data->m_forks[i]);
			i++;
		}
		free(data->m_forks);
	}
	pthread_mutex_destroy(&data->m_printf_lock);
	pthread_mutex_destroy(&data->m_death_mutex);
}

long long	what_time_is_it(void)
{
	struct timeval	data_time;

	gettimeofday(&data_time, NULL);
	return (data_time.tv_sec * 1000 + data_time.tv_usec / 1000);
}

long long	get_current_time(t_data *data)
{
	struct timeval	data_time;

	gettimeofday(&data_time, NULL);
	return ((data_time.tv_sec * 1000 + data_time.tv_usec / 1000) - data->time);
}

int	philo_atoi(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return ((int)res);
}
