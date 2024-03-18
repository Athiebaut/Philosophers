/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:53:42 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/18 00:15:06 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	which_fork_to_take(t_philo *philo, int nb, t_data *tab)
{
	if (nb == 1)
	{
		if (philo->index % 2 == 0)
		{
			if (pthread_mutex_lock(&philo->fork))
				ft_error(E_MUTEX, tab);
		}
		else
			if (pthread_mutex_lock(&philo->next->fork))
				ft_error(E_MUTEX, tab);
	}
	else
	{
		if (philo->index % 2 == 0)
		{
			if (pthread_mutex_lock(&philo->next->fork))
				ft_error(E_MUTEX, tab);
		}
		else
			if (pthread_mutex_lock(&philo->fork))
				ft_error(E_MUTEX, tab);
	}
}

static void	meal_philo2(t_philo *philo, t_data *tab)
{
	print_message(philo, M_EAT);
	if (pthread_mutex_lock(&tab->meal))
		ft_error(E_MUTEX, tab);
	philo->meals_nb++;
	if (pthread_mutex_unlock(&philo->tab->meal))
		ft_error(E_MUTEX, tab);
	if (pthread_mutex_lock(&tab->meal))
		ft_error(E_MUTEX, tab);
	philo->last_meal = get_time();
	if (pthread_mutex_unlock(&tab->meal))
		ft_error(E_MUTEX, tab);
	spend_time(tab, tab->time_to_eat);
	if (pthread_mutex_unlock(&philo->fork))
		ft_error(E_MUTEX, tab);
	if (pthread_mutex_unlock(&philo->next->fork))
		ft_error(E_MUTEX, tab);
}

static void	meal_philo(t_philo *philo)
{
	t_data	*tab;

	tab = philo->tab;
	which_fork_to_take(philo, 1, tab);
	print_message(philo, M_FORK);
	if (tab->nb_philo == 1)
	{
		spend_time(tab, tab->time_to_die);
		print_message(philo, M_DEATH);
		if (pthread_mutex_unlock(&philo->fork))
			ft_error(E_MUTEX, tab);
		tab->dead = 1;
		return ;
	}
	which_fork_to_take(philo, 2, tab);
	print_message(philo, M_FORK);
	meal_philo2(philo, tab);
}

void	*routine(void *arg)
{
	t_data	*tab;
	t_philo	*philo;

	philo = arg;
	tab = philo->tab;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (!is_philo_dead(tab) && (tab->meals_nb == -1
			|| philo->meals_nb < tab->meals_nb))
	{
		meal_philo(philo);
		print_message(philo, M_SLEEP);
		spend_time(tab, tab->time_to_sleep);
		print_message(philo, M_THINK);
		if (tab->time_to_think != -1)
			spend_time(tab, tab->time_to_think);
	}
	return (NULL);
}
