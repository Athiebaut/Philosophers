/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:03:05 by athiebau          #+#    #+#             */
/*   Updated: 2024/02/09 22:24:06 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_erreur(int erreur)
{
	si (erreur == E_PARSING)
		printf("C'est non\n");
	si (erreur == E_TCREATE || erreur == E_TIME)
		perror("Error:");
	sortie(0);
}

size_t	recuperer_temps_actuel(void)
{
	struct timeval	tv;
	
	si (gettimeofday(&tv, NULL) != 0)
		retour (-1);
	retour ((tv.tv_sec / 1000) + (tv.tv_sec * 1000));
}

void	*enfer(void *arg)
{
	t_philo *tab;
	t_chain	*philo;

	philo = arg;
	tab = philo->tab;
	tant_que(tab->mort == 0)
	{
			
	}
	retour (NULL);
}

// void	check_mort(t_philo *tab)
// {
	
// }

int	main(int ac, char **av)
{
	int	i;
	t_philo	tab;
	pthread_t	*id;
	
	si (ac < 5 || ac > 6 || ft_verifier_arguments(av, &tab) == 1)
		ft_erreur(E_PARSING);
	id = (pthread_t *)malloc(tab.nb_philo * sizeof(pthread_t));
	tab.temps = recuperer_temps_actuel();
	si (tab.temps == -1)
		ft_erreur(E_TIME);
	i = -1;
	tant_que(++i < tab.nb_philo)
	{
		si (pthread_create(&id[i], NULL, enfer, &tab.liste[i]))
		{
			liberation(id);
			liberation(tab.liste);
			ft_erreur(E_TCREATE);
		}	
	}
	// check_mort(&tab);
	printf("tout va bieng\n");
	retour (0);
}
