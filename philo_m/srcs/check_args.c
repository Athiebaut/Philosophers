/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:50:09 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/20 17:17:20 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	get_right_size(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && (str[i] < '1' || str[i] > '9'))
		i++;
	while (str[i] && (str[i] >= '1' || str[i] <= '9'))
	{
		i++;
		count++;
	}
	return (count);
		
}

static int	check_numbers(char *str, int *error)
{
	int			i;
	int			len;
	long long	result;

	i = 0;
	result = 0;
	if (!str)
	{
		*error = 1;
		return (0);
	}
	len = get_right_size(str);
	printf("len : %d\n", len);
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

static void	initialize_philo(t_data *tab)
{
	int	i;

	i = -1;
	while (++i < tab->nb_philo)
	{
		tab->list[i].index = i + 1;
		tab->list[i].meals_nb = 0;
		tab->list[i].tab = tab;
		if (i + 1 == tab->nb_philo)
			tab->list[i].next = &tab->list[0];
		else
			tab->list[i].next = &tab->list[i + 1];
		if (pthread_mutex_init(&tab->list[i].fork, NULL))
			ft_error(E_MUTEX, tab);
	}
}

static void	ft_initialisation(t_data *tab)
{
	tab->dead = 0;
	tab->satiety = 0;
	tab->list = (t_philo *)malloc(tab->nb_philo * sizeof(t_philo));
	if (!tab->list)
		ft_error(E_MALLOC, tab);
	tab->time_to_think = -1;
	if ((tab->nb_philo % 2 == 1))
	{
		if (tab->time_to_eat > tab->time_to_sleep)
			tab->time_to_think = tab->time_to_sleep + tab->time_to_eat;
		else if ((tab->time_to_eat * 3) + tab->time_to_sleep
			>= tab->time_to_die)
			tab->time_to_think = 10;
	}
	initialize_philo(tab);
	if (pthread_mutex_init(&tab->check, NULL))
		ft_error(E_MUTEX, tab);
	if (pthread_mutex_init(&tab->print, NULL))
		ft_error(E_MUTEX, tab);
	if (pthread_mutex_init(&tab->meal, NULL))
		ft_error(E_MUTEX, tab);
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
