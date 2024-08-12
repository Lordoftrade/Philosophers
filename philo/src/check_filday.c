/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:36:08 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/09 13:40:25 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

int	update_meals_and_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_number_meals);
	philo->number_meals++;
	if (philo->data->must_eat_count != 0 && philo->number_meals \
		>= philo->data->must_eat_count)
	{
		pthread_mutex_unlock(&philo->m_number_meals);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_number_meals);
	return (0);
}

int	check_philosopher_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].m_last_meal);
	if (get_current_time(data) - data->philo[i].last_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philo[i].m_last_meal);
		pthread_mutex_lock(&data->m_death_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->m_death_mutex);
		status_output(&data->philo[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].m_last_meal);
	return (0);
}

int	check_finished_meals(t_data *data, int i, \
	int *finished_philosophers)
{
	pthread_mutex_lock(&data->philo[i].m_number_meals);
	if (data->must_eat_count != 0 && data->philo[i].number_meals \
		>= data->must_eat_count)
	{
		if (data->philo[i].number_meals == data->must_eat_count)
			(*finished_philosophers)++;
		pthread_mutex_unlock(&data->philo[i].m_number_meals);
		if (*finished_philosophers == data->number_of_philosophers)
			return (1);
		return (0);
	}
	pthread_mutex_unlock(&data->philo[i].m_number_meals);
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->m_death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_death_mutex);
	return (0);
}
