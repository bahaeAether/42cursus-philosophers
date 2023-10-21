/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:57:00 by baboulou          #+#    #+#             */
/*   Updated: 2023/10/13 21:54:05 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	time_t			start;
	pthread_mutex_t	meal;
	pthread_mutex_t	display;
	pthread_mutex_t	time;
}			t_data;

typedef struct s_philo
{
	int				id;
	int				is_eating;
	int				nb_meals;
	time_t			last_eat;
	pthread_mutex_t	fork;
	t_data			*data;
	struct s_philo	*next;
}					t_philo;

t_philo			*init_philos(t_data *data);
time_t			ft_get_current_time(void);
void			ft_usleep(time_t time);
void			start_simulation(t_philo *philo, pthread_t *threads,
					t_data *data);
void			supervisor(t_philo *philo);
void			display_state(t_philo *philo, char *state);
void			ft_simulation(t_philo *philo);
void			*routine(void *arg);
void			set_philo(t_philo *tmp, t_data *data, int i, size_t start);
int				parse_args(t_data *data, int ac, char **av);
unsigned long	ft_atoi(const char *str);
int				ft_done_eating(t_philo *philo);
int				is_dead(t_philo *philo);
int				valid_args(int ac, char **av);

#endif
