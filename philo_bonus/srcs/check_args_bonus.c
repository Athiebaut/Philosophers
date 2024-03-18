/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:19:22 by alix              #+#    #+#             */
/*   Updated: 2024/03/18 01:03:32 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

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

static void	initialize_philo(t_data *tab)
{
	int	i;

	i = -1;
	while (++i < tab->nb_philo)
	{
		tab->list[i].index = i + 1;
		tab->list[i].nb_meals = 0;
		tab->list[i].tab = tab;
		if (i + 1 == tab->nb_philo)
			tab->list[i].next = &tab->list[0];
		else
			tab->list[i].next = &tab->list[i + 1];
	}
	tab->check = sem_open("/sem_check", O_CREAT);
	tab->print = sem_open("/sem_check", O_CREAT);
	tab->meal = sem_open("/sem_check", O_CREAT);
	tab->fork = sem_open("/sem_check", O_CREAT);
	if (tab->check == SEM_FAILED || tab->print == SEM_FAILED
		|| tab->meal == SEM_FAILED || tab->fork == SEM_FAILED)
		ft_error(E_SEMAPHORE, tab);
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
		tab->nb_meals = check_numbers(av[5], &error);
	else
		tab->nb_meals = -1;
	if (error == 1)
		return (1);
	ft_initialisation(tab);
	return (0);
}