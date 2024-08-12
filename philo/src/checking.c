/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/08/03 21:21:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	check_maximum(char *argv)
{
	int	i;

	i = philo_atoi(argv);
	if (i == 0 || i == -1)
		return (1);
	return (0);
}

int	check_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < 48 || argv[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	check_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Use: %s number_of_philosophers time_to_die time_to_eat \
			time_to_sleep number_of_times_each_philosopher_must_eat(not \
				 necessary)\n", argv[0]);
		return (1);
	}
	while (i < argc)
	{
		if (check_num(argv[i]))
		{
			printf("The argument must be a number and not negative\n");
			return (1);
		}
		else if (check_maximum(argv[i]))
		{
			printf("Invalid argument or more INT_MAX\n");
			return (1);
		}
		i++;
	}
	return (0);
}
