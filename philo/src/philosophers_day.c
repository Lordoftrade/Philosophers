/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_day.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:34:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/05 23:34:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

void	*monitor_die(void *arg)
{
	t_data	*data;
	int		i;
	int		finished_philosophers;

	data = (t_data *)arg;
	finished_philosophers = 0;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->m_death_mutex);
			if (data->someone_died)
				return (pthread_mutex_unlock(&data->m_death_mutex), NULL);
			pthread_mutex_unlock(&data->m_death_mutex);
			if (check_philosopher_death(data, i))
				return (NULL);
			if (check_finished_meals(data, i, &finished_philosophers))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	status_output(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->m_printf_lock);
	pthread_mutex_lock(&philo->data->m_death_mutex);
	if (!philo->data->someone_died || ft_strcmp(state, "died") == 0)
	{
		printf("Time has passed: %lldms; Filo num: %d %s\n", \
			get_current_time(philo->data), philo->person_id, state);
	}
	pthread_mutex_unlock(&philo->data->m_death_mutex);
	pthread_mutex_unlock(&philo->data->m_printf_lock);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->m_forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->m_forks[philo->l_fork_id]);
}

static void	take_forks(t_philo *philo)
{
	if (philo->l_fork_id < philo->r_fork_id)
	{
		pthread_mutex_lock(&philo->m_forks[philo->l_fork_id]);
		status_output(philo, "has taken a fork");
		pthread_mutex_lock(&philo->m_forks[philo->r_fork_id]);
		status_output(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->m_forks[philo->r_fork_id]);
		status_output(philo, "has taken a fork");
		pthread_mutex_lock(&philo->m_forks[philo->l_fork_id]);
		status_output(philo, "has taken a fork");
	}
}

void	*philosophers_day(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->person_id % 2 != 0)
		usleep(2500);
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		thinking(philo);
		if (philo->data->number_of_philosophers == 1)
			return (usleep(philo->data->time_to_eat * 1000), NULL);
		if (check_death(philo))
			return (NULL);
		take_forks(philo);
		if (check_death(philo))
			return (release_forks(philo), NULL);
		eating(philo);
		if (update_meals_and_check(philo))
			return (NULL);
		if (check_death(philo))
			return (NULL);
		sleeping(philo);
	}
	return (NULL);
}
