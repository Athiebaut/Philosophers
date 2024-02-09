/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:03:05 by athiebau          #+#    #+#             */
/*   Updated: 2024/02/09 12:54:14 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_error(int error)
{
	if (error == E_PARSING)
		printf("C'est non\n");
	if (error == E_TCREATE || error == E_TIME)
		perror("Error:");
	exit(0);
}

size_t	get_current_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec / 1000) + (tv.tv_sec * 1000));
}

void	*hell(void *arg)
{
	t_philo *tab;
	t_chain	*philo;

	philo = arg;
	tab = philo->tab;
	while(tab->death == 0)
	{
			
	}
	return (NULL);
}

// void	check_death(t_philo *tab)
// {
	
// }

int	main(int ac, char **av)
{
	int	i;
	t_philo	tab;
	pthread_t	*id;
	
	if (ac < 5 || ac > 6 || check_args(av, &tab) == 1)
		ft_error(E_PARSING);
	id = (pthread_t *)malloc(tab.nb_philo * sizeof(pthread_t));
	tab.time = get_current_time();
	if (tab.time == -1)
		ft_error(E_TIME);
	i = -1;
	while(++i < tab.nb_philo)
	{
		if (pthread_create(&id[i], NULL, hell, &tab.list[i]))
		{
			free(id);
			free(tab.list);
			ft_error(E_TCREATE);
		}	
	}
	// check_death(&tab);
	printf("tout va bieng\n");
	return (0);
}
