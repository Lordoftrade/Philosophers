/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:05:47 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/09 14:09:38 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

void	sleeping(t_philo *philo)
{
	status_output(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->m_last_meal);
	status_output(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	release_forks(philo);
}

void	thinking(t_philo *philo)
{
	status_output(philo, "is thinking");
	usleep(100);
}
