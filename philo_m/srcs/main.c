/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:03:05 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/20 17:12:39 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	the_end(t_data *tab);

void	ft_error(int error, t_data *tab)
{
	if (error == E_PARSING)
		printf("Error: Invalids parameters\n");
	else
		perror("Error:");
	if (tab && tab->list)
		free(tab->list);
	if (tab && tab->id)
		free(tab->id);
	exit(1);
}

void	the_end(t_data *tab)
{
	int	i;

	i = -1;
	while (++i < tab->nb_philo)
		if (pthread_join(tab->id[i], NULL))
			ft_error(E_THREAD, tab);
	i = -1;
	while (++i < tab->nb_philo)
	{
		if (pthread_mutex_destroy(&tab->list[i].fork))
			ft_error(E_MUTEX, tab);
	}
	if (pthread_mutex_destroy(&tab->print))
		ft_error(E_MUTEX, tab);
	if (pthread_mutex_destroy(&tab->check))
		ft_error(E_MUTEX, tab);
	if (pthread_mutex_destroy(&tab->meal))
		ft_error(E_MUTEX, tab);
	free(tab->list);
	free(tab->id);
}

static void	create_threads(pthread_t *id, t_data *tab)
{
	int	i;

	i = -1;
	while (++i < tab->nb_philo)
	{
		if (pthread_create(&id[i], NULL, &routine, &tab->list[i]) != 0)
		{
			free(id);
			free(tab->list);
			ft_error(E_THREAD, tab);
		}
		if (pthread_mutex_lock(&tab->meal))
			ft_error(E_MUTEX, tab);
		tab->list[i].last_meal = tab->time_0;
		if (pthread_mutex_unlock(&tab->meal))
			ft_error(E_MUTEX, tab);
	}
}

int	main(int ac, char **av)
{
	t_data		tab;

	if (ac < 5 || ac > 6 || check_args(av, &tab) == 1)
		ft_error(E_PARSING, NULL);
	tab.id = (pthread_t *)malloc(tab.nb_philo * sizeof(pthread_t));
	if (!tab.id)
		ft_error(E_MALLOC, &tab);
	tab.time_0 = get_time();
	if (tab.time_0 == -1)
		ft_error(E_TIME, &tab);
	create_threads(tab.id, &tab);
	(check_death_and_satiety(&tab), the_end(&tab));
	return (0);
}
