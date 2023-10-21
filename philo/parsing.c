/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:33:34 by baboulou          #+#    #+#             */
/*   Updated: 2023/10/13 21:34:41 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: wrong arguments\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_args(t_data *data, int ac, char **av)
{
	if (!data || !valid_args(ac, av))
		return (0);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if (!data->nb_philo || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->nb_must_eat)
	{
		printf("Error: arguments cannot overflow or be null\n");
		return (0);
	}
	if (data->nb_philo > 200)
	{
		printf("Error: too many philosophers\n");
		return (0);
	}
	pthread_mutex_init(&data->display, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->meal, NULL);
	return (1);
}

void	set_philo(t_philo *tmp, t_data *data, int i, size_t start)
{
	tmp->id = i + 1;
	tmp->is_eating = 0;
	tmp->nb_meals = 0;
	tmp->data = data;
	data->start = start;
	tmp->last_eat = data->start;
	pthread_mutex_init(&tmp->fork, NULL);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;
	size_t	start;

	i = 0;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	tmp = philo;
	start = ft_get_current_time();
	while (i < data->nb_philo)
	{
		set_philo(tmp, data, i, start);
		if (i < data->nb_philo - 1)
		{
			tmp->next = malloc(sizeof(t_philo));
			if (!tmp->next)
				return (0);
			tmp = tmp->next;
		}
		i++;
	}
	tmp->next = philo;
	return (philo);
}
