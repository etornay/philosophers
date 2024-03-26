/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:29:16 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/26 19:27:28 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eat(t_data *philo)
{
	t_program	*p;

	p = philo->program;
	pthread_mutex_lock(&p->meal_mutex_lock);
	if (philo->philo_eat_time == p->number_of_meals)
	{
		pthread_mutex_lock(&p->time_lock);
		p->all_philos_eaten++;
		pthread_mutex_unlock(&p->time_lock);
	}
	pthread_mutex_unlock(&p->meal_mutex_lock);
	pthread_mutex_lock(&p->time_lock);
	if (p->all_philos_eaten == p->number_of_philos)
	{
		pthread_mutex_lock(&p->dead_lock);
		p->finish = 1;
		pthread_mutex_unlock(&p->dead_lock);
		pthread_mutex_unlock(&p->time_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	philos_eat(t_data *philo)
{
	t_program	*p;

	p = philo->program;
	pthread_mutex_lock(&p->forks[philo->left_fork_id]);
	printf_philos(p, philo->philos_id, "has taken a fork");
	pthread_mutex_lock(&p->forks[philo->right_fork_id]);
	printf_philos(p, philo->philos_id, "has taken another fork");
	pthread_mutex_lock(&p->meal_lock);
	printf_philos(p, philo->philos_id, "is eating");
	pthread_mutex_lock(&p->time_lock);
	philo->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&p->time_lock);
	philo->philo_eat_time++;
	pthread_mutex_unlock(&p->meal_lock);
	check_eat(philo);
	ft_usleep(p, p->time_2_eat);
	pthread_mutex_unlock(&p->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&p->forks[philo->right_fork_id]);
}

int	check_end(t_program *p)
{
	pthread_mutex_lock(&p->dead_lock);
	if (p->finish == 1)
	{
		pthread_mutex_unlock(&p->dead_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&p->dead_lock);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *philo)
{
	t_program	*program;
	t_data		*p;

	p = philo;
	program = p->program;
	if (p->philos_id % 2)
		ft_usleep(program, 5);
	while (!check_end(program))
	{
		philos_eat(p);
		printf_philos(program, p->philos_id, "is sleeping");
	}
	return (NULL);
}