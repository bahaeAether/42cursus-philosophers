/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 06:57:27 by baboulou          #+#    #+#             */
/*   Updated: 2023/10/13 21:34:34 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atoi(const char *str)
{
	unsigned long	r;

	r = 0;
	while (*str)
	{
		r = r * 10 + (*str++ - 48);
		if (r > 2147483647)
			return (0);
	}
	return (r);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = ft_get_current_time();
	while (ft_get_current_time() - start < time)
		usleep(100);
}

time_t	ft_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*threads;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		if (!parse_args(data, ac, av))
			return (1);
		threads = malloc(sizeof(pthread_t) * data->nb_philo);
		philo = init_philos(data);
		if (!philo)
			return (1);
		start_simulation(philo, threads, data);
		supervisor(philo);
	}
	else
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	return (0);
}
