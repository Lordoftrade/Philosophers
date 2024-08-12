/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/29 19:21:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

void	philo_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		pthread_mutex_destroy(&data->philo[i].m_last_meal);
		pthread_mutex_destroy(&data->philo[i].m_number_meals);
		i++;
	}
	pthread_mutex_destroy(&data->m_printf_lock);
	pthread_mutex_destroy(&data->m_death_mutex);
}

void	philo_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
}

int	init_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		init_philosopher(data, i);
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
			return (free_data(data), 1);
		if (pthread_mutex_init(&(data->philo[i].m_last_meal), NULL) != 0 \
			|| pthread_mutex_init(&(data->philo[i].m_number_meals), NULL) != 0)
			return (free_data(data), 1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philosophers_day,
				&data->philo[i]) != 0)
			return (free_data(data), 1);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_die, data) != 0)
		return (free_data(data), 1);
	philo_join(data);
	return (philo_destroy(data), 0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = philo_atoi(argv[5]);
	else
		data->must_eat_count = 0;
	data->time = what_time_is_it();
	data->someone_died = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->m_forks = malloc(sizeof(pthread_mutex_t) \
		* data->number_of_philosophers);
	if (!data->philo || !data->m_forks)
		return (free_data(data), 1);
	if (pthread_mutex_init(&data->m_printf_lock, NULL) != 0 \
		||pthread_mutex_init(&data->m_death_mutex, NULL) != 0)
	{
		free(data->m_forks);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_argv(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) == 0)
	{
		if (init_simulation(&data) != 0)
		{
			free_data(&data);
			return (1);
		}
	}
	else
	{
		write(2, "Error init data\n", 16);
		free_data(&data);
		return (1);
	}
	free_data(&data);
	return (0);
}
