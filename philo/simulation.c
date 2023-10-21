/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:14:08 by baboulou          #+#    #+#             */
/*   Updated: 2023/10/13 21:17:30 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->display);
	printf("%ld: %d %s\n", ft_get_current_time() - philo->data->start,
		philo->id, state);
	pthread_mutex_unlock(&philo->data->display);
}

void	ft_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	display_state(philo, "has taken a fork");
	display_state(philo, "is eating");
	pthread_mutex_lock(&philo->data->time);
	philo->last_eat = ft_get_current_time();
	pthread_mutex_unlock(&philo->data->time);
	pthread_mutex_lock(&philo->data->meal);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->data->meal);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	display_state(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	display_state(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1337)
		ft_simulation(philo);
}

void	start_simulation(t_philo *philo, pthread_t *threads, t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	while (i < data->nb_philo)
	{
		pthread_create(&threads[i], NULL, &routine, tmp);
		pthread_detach(threads[i]);
		tmp = tmp->next->next;
		i += 2;
	}
	usleep(300);
	i = 1;
	tmp = philo->next;
	while (i < data->nb_philo)
	{
		pthread_create(&threads[i], NULL, &routine, tmp);
		pthread_detach(threads[i]);
		tmp = tmp->next->next;
		i += 2;
	}
}
