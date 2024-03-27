/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:45:22 by alix              #+#    #+#             */
/*   Updated: 2024/03/27 04:11:54 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static void	meal_philo(t_philo *philo)
{
	t_data	*tab;

	tab = philo->tab;
	sem_wait(philo->tab->fork);
	print_message(philo, M_FORK);
	if (philo->tab->nb_philo == 1)
	{
		spend_time(philo, tab->time_to_die);
		print_message(philo, M_DEATH);
		tab->dead = 1;
		sem_post(philo->tab->fork);
		return ;
	}
	sem_wait(philo->tab->fork);
	print_message(philo, M_FORK);
	sem_wait(tab->meal);
	philo->last_meal = get_time();
	sem_post(tab->meal);
	print_message(philo, M_EAT);
	spend_time(philo, tab->time_to_eat);
	sem_wait(tab->meal);
	philo->nb_meals++;
	sem_post(tab->meal);
	sem_post(tab->fork);
	sem_post(tab->fork);
}

void	*routine(void *arg)
{
	t_data	*tab;
	t_philo	*philo;

	philo = arg;
	tab = philo->tab;
	philo->last_meal = tab->time_0;
	pthread_create(&philo->death_satiety, NULL, check_death_and_satiety, (void *)philo);
	if (philo->index % 2 == 0)
		usleep(1000);
	while (!test_death(tab))
	{
		meal_philo(philo);
		if (test_meals(philo))
			break ;
		print_message(philo, M_SLEEP);
		spend_time(philo, tab->time_to_sleep);
		print_message(philo, M_THINK);
		if (tab->time_to_think != -1)
			spend_time(philo, tab->time_to_think);
	}
	pthread_join(philo->death_satiety, NULL);
	exit (0);
}