/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:45:22 by alix              #+#    #+#             */
/*   Updated: 2024/03/26 02:10:59 by athiebau         ###   ########.fr       */
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
		spend_time(tab, tab->time_to_die);
		print_message(philo, M_DEATH);
		tab->dead = 1;
		sem_post(philo->tab->fork);
		exit (1);
	}
	// sem_wait(tab->check);
	// philo->last_meal = get_time();
	// sem_post(philo->tab->check);
	sem_wait(philo->tab->fork);
	print_message(philo, M_FORK);
	sem_wait(philo->tab->check);
	philo->nb_meals++;
	print_message(philo, M_EAT);
	philo->last_meal = get_time();
	sem_post(philo->tab->check);
	spend_time(tab, tab->time_to_eat);
	sem_post(philo->tab->fork);
	sem_post(philo->tab->fork);
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
	while (!tab->dead)
	{
		meal_philo(philo);
		if (tab->nb_meals != -1 && philo->nb_meals >= tab->nb_meals)
			break ;
		print_message(philo, M_SLEEP);
		spend_time(tab, tab->time_to_sleep);
		print_message(philo, M_THINK);
	}
	pthread_join(philo->death_satiety, NULL);
	exit (0);
}