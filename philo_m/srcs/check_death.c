/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:52:13 by alix              #+#    #+#             */
/*   Updated: 2024/03/22 15:43:16 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	test_satiety(t_data *tab)
{
	if (pthread_mutex_lock(&tab->meal))
		ft_error(E_MUTEX, tab);
	if (tab->satiety)
	{
		if (pthread_mutex_unlock(&tab->meal))
			ft_error(E_MUTEX, tab);
		return (true);
	}
	if (pthread_mutex_unlock(&tab->meal))
		ft_error(E_MUTEX, tab);
	return (false);
}

bool	test_death(t_data *tab)
{
	if (pthread_mutex_lock(&tab->check))
		ft_error(E_MUTEX, tab);
	if (tab->dead)
	{
		if (pthread_mutex_unlock(&tab->check))
			ft_error(E_MUTEX, tab);
		return (true);
	}
	if (pthread_mutex_unlock(&tab->check))
		ft_error(E_MUTEX, tab);
	return (false);
}

static bool	check_death(t_data *tab, int i)
{
	long long	time;

	if (pthread_mutex_lock(&tab->meal))
		ft_error(E_MUTEX, tab);
	time = get_time();
	if (time == -1)
		ft_error(E_TIME, tab);
	if ((time - tab->list[i].last_meal) > tab->time_to_die)
	{
		if (pthread_mutex_unlock(&tab->meal))
			ft_error(E_MUTEX, tab);
		return (true);
	}
	if (pthread_mutex_unlock(&tab->meal))
		ft_error(E_MUTEX, tab);
	return (false);
}

static void	check_meals(t_data *tab)
{
	int	i;

	i = 0;
	if (pthread_mutex_lock(&tab->meal))
		ft_error(E_MUTEX, tab);
	while (tab->meals_nb != -1 && i < tab->nb_philo
		&& (tab->list[i].meals_nb >= tab->meals_nb))
		i++;
	if (i == tab->nb_philo)
		tab->satiety = 1;
	if (pthread_mutex_unlock(&tab->meal))
		ft_error(E_MUTEX, tab);
}

void	check_death_and_satiety(t_data *tab)
{
	int	i;

	while (!test_satiety(tab))
	{
		i = -1;
		while (!test_death(tab) && ++i < tab->nb_philo)
		{
			if ((check_death(tab, i)))
			{
				if (pthread_mutex_lock(&tab->check))
					ft_error(E_MUTEX, tab);
				tab->dead = 1;
				if (pthread_mutex_unlock(&tab->check))
					ft_error(E_MUTEX, tab);
				if (tab->nb_philo != 1)
					print_message(&tab->list[i], M_DEATH);
				break ;
			}
			//usleep(1);
		}
		usleep(1);
		if (test_death(tab))
			break ;
		check_meals(tab);
	}
}
