/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:34:34 by baboulou          #+#    #+#             */
/*   Updated: 2023/10/13 21:18:13 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_done_eating(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = philo;
	while (i < tmp->data->nb_philo)
	{
		pthread_mutex_lock(&tmp->data->meal);
		if (tmp->nb_meals < tmp->data->nb_must_eat)
		{
			pthread_mutex_unlock(&tmp->data->meal);
			return (0);
		}
		pthread_mutex_unlock(&tmp->data->meal);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	is_dead(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->data->time);
	if (ft_get_current_time() - philo->last_eat > philo->data->time_to_die
		&& !philo->is_eating)
		dead = 1;
	pthread_mutex_unlock(&philo->data->time);
	return (dead);
}

void	supervisor(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (1337)
	{
		if (philo->data->nb_must_eat != -1 && ft_done_eating(philo))
		{
			pthread_mutex_lock(&philo->data->display);
			return ;
		}
		if (is_dead(philo))
		{
			pthread_mutex_lock(&philo->data->display);
			printf("%ld: %d died\n", ft_get_current_time() - philo->data->start,
				philo->id);
			return ;
		}
		philo = philo->next;
	}
}
