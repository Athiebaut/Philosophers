/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:11:00 by athiebau          #+#    #+#             */
/*   Updated: 2024/02/08 16:11:58 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_check_numbers(char *str, int *error)
{
	int	i;
	int	len;
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

static void	ft_initiate(t_philo *tab)
{
	int	i;
	
	i = 0;
	tab->death = 0;
	tab->list = (t_chain *)malloc(tab->nb_philo * sizeof(t_chain));
	while(i < tab->nb_philo)
	{
		tab->list[i].index = i + 1;
		tab->list[i].nb_lunch = 0;
		tab->list[i].tab = tab;
		if (i < tab->nb_philo)
			tab->list[i].next = &tab->list[i + 1];
		else
			tab->list[i].next = &tab->list[0];
		if (i > 0)
			tab->list[i].previous = &tab->list[i - 1];
		else
			tab->list[i].previous = &tab->list[tab->nb_philo - 1];
		pthread_mutex_init(&tab->list[i].fork, NULL);
		i++;
	}
}

int	check_args(char **av, t_philo *tab)
{
	int	error;

	error = 0;
	tab->nb_philo = ft_check_numbers(av[1], &error);
	tab->time_to_die = ft_check_numbers(av[2], &error);
	tab->time_to_eat = ft_check_numbers(av[3], &error);
	tab->time_to_sleep = ft_check_numbers(av[4], &error);
	if (av[5])
		tab->nb_lunch = ft_check_numbers(av[2], &error);
	else
		tab->nb_lunch = -1;
	if (error == 1)
		return (1);
	ft_initiate(tab);
	return (0);
}