/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:53:42 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/14 18:32:01 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	meal_philo(t_philo *philo)
{
	t_data	*tab;

	tab = philo->tab;
	if (philo->index % 2 == 0)
		pthread_mutex_lock(&philo->fork);
	else
		pthread_mutex_lock(&philo->next->fork);
	print_message(philo, M_FORK);
	if (tab->nb_philo == 1)
	{
		spend_time(tab, tab->time_to_die);
		print_message(philo, M_DEATH);
		pthread_mutex_unlock(&philo->fork);
		tab->dead = 1;
		return ;
	}
	if (philo->index % 2 == 0)
		pthread_mutex_lock(&philo->next->fork);
	else
		pthread_mutex_lock(&philo->fork);
		
	print_message(philo, M_FORK);
	pthread_mutex_lock(&tab->meal);
	philo->meals_nb++;
	pthread_mutex_unlock(&philo->tab->meal);
	print_message(philo, M_EAT);
	pthread_mutex_lock(&tab->meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&tab->meal);
	spend_time(tab, tab->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*routine(void *arg)
{
	t_data	*tab;
	t_philo	*philo;

	philo = arg;
	tab = philo->tab;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (!is_philo_dead(tab) && (tab->meals_nb == -1 || philo->meals_nb < tab->meals_nb))
	{
		meal_philo(philo);
		print_message(philo, M_SLEEP);
		spend_time(tab, tab->time_to_sleep);
		print_message(philo, M_THINK);
		if (tab->time_to_think != -1 || philo->index % 2 == 0)
			spend_time(tab, tab->time_to_think);
	}
	return (NULL);
}
