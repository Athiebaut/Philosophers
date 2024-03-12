/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:03:05 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/12 20:04:25 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_death(t_data *tab)
{
	int	i;

	while (tab->satiety)
	{
		i = -1;
		while (!tab->dead && ++i < tab->nb_philo)
		{
			pthread_mutex_lock(&tab->check);
			if ((get_time() - tab->list[i].last_meal) > (size_t)tab->time_to_die)
			{
				print_message(&tab->list[i], M_DEATH);
				tab->dead = 1;
			}
			pthread_mutex_unlock(&tab->check);
			//usleep(100);
		}
		if (tab->dead == 1)
			break ;
		i = 0;
		while (tab->meals_nb != -1 && i < tab->nb_philo && tab->list[i].meals_nb >= tab->meals_nb)
			i++;
		if (i == tab->nb_philo)
			tab->satiety = 1;
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
	free(tab->list);
	free(id);
}

int	main(int ac, char **av)
{
	int	i;
	t_data	tab;
	pthread_t	*id;
	
	if(ac < 5 || ac > 6 || check_args(av, &tab) == 1)
		ft_error(E_PARSING);
	id = (pthread_t *)malloc(tab.nb_philo * sizeof(pthread_t));
	tab.time_0 = get_time();
	if (tab.time_0 == -1)
		ft_error(E_TIME);
	i = -1;
	while(++i < tab.nb_philo)
	{
		if(pthread_create(&id[i], NULL, &routine, &tab.list[i]) != 0)
		{
			free(id);
			free(tab.list);
			ft_error(E_TCREATE);
		}
		pthread_mutex_lock(&tab.check);
		tab.list[i].last_meal = tab.time_0;
		pthread_mutex_unlock(&tab.check);
	}
	i = -1;
	while (++i < tab.nb_philo)
		pthread_join(id[i], NULL);
	check_death(&tab);
	the_end(&tab, id);
	return (0);
}
