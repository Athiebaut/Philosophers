/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:50:09 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/14 18:31:27 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_numbers(char *str, int *error)
{
	int			i;
	int			len;
	long long	result;

	i = 0;
	result = 0;
	len = ft_strlen(str);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		*error = 1;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			*error = 1;
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (len > 10)
		*error = 1;
	if (result > INT_MAX)
		*error = 1;
	return (result);
}

static void	ft_initialisation(t_data *tab)
{
	int	i;

	i = -1;
	tab->dead = 0;
	tab->satiety = 0;
	tab->list = (t_philo *)malloc(tab->nb_philo * sizeof(t_philo));
	tab->time_to_think = -1;
	if ((tab->nb_philo % 2 == 1) && ((tab->time_to_sleep + tab->time_to_eat) < tab->time_to_die))
	{
		if (tab->time_to_eat > tab->time_to_sleep)
			tab->time_to_think = tab->time_to_eat / 2;
		else
			tab->time_to_think = tab->time_to_sleep / 2; 
	}
	else		
		tab->time_to_think = -1;
	while (++i < tab->nb_philo)
	{
		tab->list[i].index = i + 1;
		tab->list[i].meals_nb = 0;
		tab->list[i].tab = tab;
		if (i + 1 == tab->nb_philo)
			tab->list[i].next = &tab->list[0];
		else
			tab->list[i].next = &tab->list[i + 1];
		pthread_mutex_init(&tab->list[i].fork, NULL);
	}
	pthread_mutex_init(&tab->check, NULL);
	pthread_mutex_init(&tab->print, NULL);
	pthread_mutex_init(&tab->meal, NULL);
}

int	check_args(char **av, t_data *tab)
{
	int	error;

	error = 0;
	tab->nb_philo = check_numbers(av[1], &error);
	tab->time_to_die = check_numbers(av[2], &error);
	tab->time_to_eat = check_numbers(av[3], &error);
	tab->time_to_sleep = check_numbers(av[4], &error);
	if (av[5])
		tab->meals_nb = check_numbers(av[5], &error);
	else
		tab->meals_nb = -1;
	if (error == 1)
		return (1);
	ft_initialisation(tab);
	return (0);
}
