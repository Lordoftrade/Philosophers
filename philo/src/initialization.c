/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:14:31 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/09 14:14:47 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

void	init_philosopher(t_data *data, int i)
{
	data->philo[i].person_id = i + 1;
	data->philo[i].l_fork_id = i;
	data->philo[i].r_fork_id = (i + 1) % data->number_of_philosophers;
	data->philo[i].last_meal = get_current_time(data);
	data->philo[i].number_meals = 0;
	data->philo[i].time_to_eat = data->time_to_eat;
	data->philo[i].time_to_sleep = data->time_to_sleep;
	data->philo[i].m_forks = data->m_forks;
	data->philo[i].m_printf_lock = &data->m_printf_lock;
	data->philo[i].data = data;
}
