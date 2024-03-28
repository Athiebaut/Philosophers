/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:58:01 by vleida            #+#    #+#             */
/*   Updated: 2024/03/28 06:05:38 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static void	init_forks(t_tab *tab)
{
	int			i;
	pid_t		cur_pid;
	t_philo		*philo;

	i = 0;
	philo = tab->philo;
	tab->time_0 = get_time();
	philo->startime_to_eat = tab->time_0;
	while (i < tab->nb_philo)
	{
		philo->index = i + 1;
		cur_pid = fork();
		if (!cur_pid)
		{
			routine(philo);
			break ;
		}
		else if (cur_pid == -1)
			(printf("Error: fork error\n"), exit(-1));
		else
			tab->pid_all[i] = cur_pid;
		i++;
	}
}

static void	monitoring(t_tab *tab, int dead)
{
	int	i;
	int	check;

	(void)dead;
	while (tab->nb_full < tab->nb_philo)
	{
		waitpid(-1, &check, 0);
		if (WIFEXITED(check) && WEXITSTATUS(check) == 1)
		{
			tab->dead++;
			break ;
		}
		else if (WIFEXITED(check) && WEXITSTATUS(check) == 2)
			tab->nb_full++;
	}
	if (tab->dead)
	{
		i = 0;
		while (i < tab->nb_philo)
			(kill(tab->pid_all[i], SIGKILL), i++);
	}
	if (tab->nb_full == tab->nb_philo && !tab->dead)
		sem_close(tab->print);
}

int	main(int ac, char **av)
{
	t_tab	tab;

	if (ac != 5 && ac != 6)
	{
		tab.error_fl = -1;
		printf("Error: invalid input\n");
		return (0);
	}
	init_tab(av, &tab, ac);
	if (tab.error_fl)
		return (0);
	init_forks(&tab);
	monitoring(&tab, 0);
	usleep(1000000);
	ft_free_all(&tab);
	if (tab.nb_meals_total == -1)
	{
		sem_post(tab.print);
		sem_close(tab.print);
	}
	return (0);
}
