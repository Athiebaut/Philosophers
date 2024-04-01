/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:57:55 by vleida            #+#    #+#             */
/*   Updated: 2024/03/28 05:57:03 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static int	check_numbers(char	*str, t_tab *tab)
{
	int				neg;
	unsigned long	res;

	neg = 1;
	res = 0;
	while (*str && *str == 32)
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9' && res <= -MN_INT)
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	if (*str != 0 || neg < 0 || (res > MX_INT && neg > 0))
		tab->error_fl--;
	return ((int)res * neg);
}

static void	init_philo(t_tab *tab)
{
	int	i;

	if (tab->error_fl)
		return ;
	i = 0;
	tab->philo->index = i + 1;
	tab->philo->fl = 0;
	tab->philo->state = 0;
	tab->philo->nb_meals = 0;
	tab->philo->last_meal = 0;
	tab->philo->startime_to_eat = 0;
	tab->philo->tab = tab;
	tab->exception = 0;
	if (tab->nb_philo % 2 && tab->time_to_eat * 3 > tab->time_to_die)
		tab->exception = 1;
}

static void	init_malloc(t_tab *tab)
{
	pid_t	*tmp;
	t_philo	*philos;

	tmp = malloc(sizeof(pid_t) * (tab->nb_philo));
	if (!tmp)
	{
		tab->error_fl--;
		return ;
	}
	philos = malloc(sizeof(t_philo));
	if (!philos)
	{
		free(tmp);
		tab->error_fl--;
		return ;
	}
	tab->pid_all = tmp;
	tab->philo = philos;
}

static void	init_sema(t_tab *tab)
{
	(sem_unlink("forks"), sem_unlink("print"));
	tab->forks = sem_open("forks", O_RDONLY | O_CREAT, 0664, tab->nb_philo);
	if (tab->forks == SEM_FAILED)
	{
		tab->error_fl--;
		printf("Error: opening semaphore\n");
		return ;
	}
	tab->print = sem_open("print", O_RDONLY | O_CREAT, 0664, 1);
	if (tab->print == SEM_FAILED)
	{
		tab->error_fl--;
		printf("Error: opening semaphore\n");
		return ;
	}
}

void	init_tab(char **av, t_tab *tab, int ac)
{
	tab->error_fl = 0;
	tab->nb_full = 0;
	tab->dead = 0;
	tab->nb_philo = check_numbers(av[1], tab);
	tab->time_to_die = check_numbers(av[2], tab);
	tab->time_to_eat = check_numbers(av[3], tab);
	tab->time_to_sleep = check_numbers(av[4], tab);
	tab->nb_meals_total = -1;
	if (ac == 6)
		tab->nb_meals_total = check_numbers(av[5], tab);
	tab->time_0 = 0;
	if (tab->error_fl || !tab->nb_philo || !tab->time_to_die)
	{
		tab->error_fl--;
		printf("Error: invalid input\n");
		return ;
	}
	init_malloc(tab);
	init_philo(tab);
	if (tab->error_fl)
		printf("Error: Allocation fail\n");
	init_sema(tab);
}
