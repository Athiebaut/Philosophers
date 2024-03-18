/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:45:22 by alix              #+#    #+#             */
/*   Updated: 2024/03/18 01:49:06 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static void	philo_mange(t_philo *philo)
{
	t_table	*tab;

	tab = philo->tab;
	sem_wait(philo->tab->fourchette);
	afficher_message(philo, MESSAGE_FOURCHETTE);
	if (philo->tab->nombre_de_philos == 1)
	{
		passe_temps(tab, tab->temps_de_famine);
		afficher_message(philo, MESSAGE_MORT);
		tab->mort = 1;
		return ;
	}
	sem_wait(philo->tab->fourchette);
	afficher_message(philo, MESSAGE_FOURCHETTE);
	sem_wait(philo->tab->verifier);
	philo->nombre_manger++;
	afficher_message(philo, MESSAGE_MANGER);
	philo->dernier_repas = temps_actuel();
	sem_post(philo->tab->verifier);
	passe_temps(tab, tab->temps_de_manger);
	sem_post(philo->tab->fourchette);
	sem_post(philo->tab->fourchette);
}

void	*la_vie(void *arg)
{
	t_philo	*philo;
	t_data	*tab;

	philo = arg;
	tab = philo->tab;
	philo->last_meal = tab->time_0;
	pthread_create(&philo->death_satiety, NULL, check_death, philo);
	if (philo->index % 2 == 0)
		usleep(1000);
	while (!tab->dead)
	{
		philo_mange(philo);
		if (tab->nb_meals != -1 && philo->nb_meals >= tab->nb_meals)
			break ;
		afficher_message(philo, MESSAGE_SOMMEIL);
		passe_temps(tab, tab->temps_de_sommeil);
		afficher_message(philo, MESSAGE_PENSER);
	}
	pthread_join(philo->verifier_dead, NULL);
	exit (0);
}