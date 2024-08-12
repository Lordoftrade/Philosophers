/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:14:46 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/09 12:14:46 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILO_H
# define FILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo
{
	int				person_id;
	int				l_fork_id;
	int				r_fork_id;
	long long		last_meal;
	int				number_meals;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_last_meal;
	pthread_mutex_t	m_number_meals;
	pthread_mutex_t	*m_printf_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	long long		time;
	t_philo			*philo;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_printf_lock;
	pthread_t		monitor_thread;
	pthread_mutex_t	m_death_mutex;
}	t_data;

int			check_argv(int argc, char **argv);
int			philo_atoi(const char *str);
long long	what_time_is_it(void);
long long	get_current_time(t_data *data);
void		*philosophers_day(void *arg);
void		status_output(t_philo *philo, char *state);
void		*monitor_die(void *arg);
void		free_data(t_data *data);
void		ft_usleep(int ms);
int			ft_strcmp(const char *s1, const char *s2);
int			check_philosopher_death(t_data *data, int i);
int			check_finished_meals(t_data *data, int i, \
			int *finished_philosophers);
int			check_death(t_philo *philo);
int			update_meals_and_check(t_philo *philo);
void		thinking(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		release_forks(t_philo *philo);
void		init_philosopher(t_data *data, int i);

#endif
