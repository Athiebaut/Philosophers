/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:03:05 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/15 17:30:59 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	test_satiety(t_data *tab)
{
	pthread_mutex_lock(&tab->meal);
	if (tab->satiety)
	{
		pthread_mutex_unlock(&tab->meal);
		return (true);
	}
	pthread_mutex_unlock(&tab->meal);
	return (false);
}

bool	test_death(t_data *tab)
{
	pthread_mutex_lock(&tab->check);
	if (tab->dead)
	{
		pthread_mutex_unlock(&tab->check);
		return (true);
	}
	pthread_mutex_unlock(&tab->check);
	return (false);
}

bool	envie_de_crever(t_data *tab, int i)
{
	pthread_mutex_lock(&tab->meal);
	if ((get_time() - tab->list[i].last_meal) > tab->time_to_die)
	{
		pthread_mutex_unlock(&tab->meal);
		return (true);
	}
	pthread_mutex_unlock(&tab->meal);
	return (false);
}

void	check_death(t_data *tab)
{
	int	i;

	while (!test_satiety(tab))
	{
		i = -1;
		while (!test_death(tab) && ++i < tab->nb_philo)
		{
			if ((envie_de_crever(tab, i)))
			{
				pthread_mutex_lock(&tab->check);
				tab->dead = 1;
				pthread_mutex_unlock(&tab->check);
				if (tab->nb_philo != 1)
					print_message(&tab->list[i], M_DEATH);
				break ;
			}
			usleep(1);
		}
		if (test_death(tab))
			break ;
		i = 0;
		pthread_mutex_lock(&tab->meal);
		while (tab->meals_nb != -1 && i < tab->nb_philo
			&& (tab->list[i].meals_nb >= tab->meals_nb))
			i++;
		if (i == tab->nb_philo)
			tab->satiety = 1;
		pthread_mutex_unlock(&tab->meal);
	}
}

void	the_end(t_data *tab, pthread_t *id)
{
	int	i;

	i = -1;
	while (++i < tab->nb_philo)
		pthread_join(id[i], NULL);
	i = -1;
	while (++i < tab->nb_philo)
		pthread_mutex_destroy(&tab->list[i].fork);
	pthread_mutex_destroy(&tab->print);
	pthread_mutex_destroy(&tab->check);
	pthread_mutex_destroy(&tab->meal);
	free(tab->list);
	free(id);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		tab;
	pthread_t	*id;

	if (ac < 5 || ac > 6 || check_args(av, &tab) == 1)
		ft_error(E_PARSING);
	id = (pthread_t *)malloc(tab.nb_philo * sizeof(pthread_t));
	tab.time_0 = get_time();
	if (tab.time_0 == -1)
		ft_error(E_TIME);
	i = -1;
	while (++i < tab.nb_philo)
	{
		if (pthread_create(&id[i], NULL, &routine, &tab.list[i]) != 0)
		{
			free(id);
			free(tab.list);
			ft_error(E_TCREATE);
		}
		pthread_mutex_lock(&tab.meal);
		tab.list[i].last_meal = tab.time_0;
		pthread_mutex_unlock(&tab.meal);
	}
	(check_death(&tab), the_end(&tab, id));
	return (0);
}
