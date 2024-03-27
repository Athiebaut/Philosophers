/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:53:44 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/27 04:19:02 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

bool	test_death(t_data *tab)
{
	sem_wait(tab->check);
	if (tab->dead)
	{
		sem_post(tab->check);
		return (true);
	}
	sem_post(tab->check);
	return (false);
}

bool	test_meals(t_philo *philo)
{	
	sem_wait(philo->tab->meal);
	if (philo->tab->nb_meals != -1 && philo->nb_meals >= philo->tab->nb_meals)
	{
		sem_post(philo->tab->meal);
		return (true);
	}
	sem_post(philo->tab->meal);
	return (false);
}

static bool	check_death(t_philo *philo)
{
	long long	time;
	
	sem_wait(philo->tab->meal);
	time = get_time();
	if (time == -1)
		ft_error(E_TIME, philo->tab);
	if (((time - philo->last_meal) > philo->tab->time_to_die) && philo->tab->nb_philo != 1)
	{
		sem_post(philo->tab->meal);
		return (true);
	}
	sem_post(philo->tab->meal);
	return (false);
}

void	*check_death_and_satiety(void *arg)
{
	t_philo	*philo;
	t_data	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	while (1)
	{
		if (check_death(philo))
		{
			print_message(philo, M_DEATH);
			sem_wait(tab->check);
			tab->dead = 1;
			sem_post(tab->check);
			exit (1);
		}
		if (tab->dead)
			break ;
		if (test_meals(philo))
			break ;
		//usleep(1);
	}
	return (NULL);
}

void	the_end(t_data *tab)
{
	int	i;
	int	status;

	i = -1;
	while (++i < tab->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < tab->nb_philo)
				kill(tab->list[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(tab->print);
	sem_close(tab->check);
	sem_close(tab->fork);
	sem_close(tab->meal);
	sem_unlink("/sem_print");
	sem_unlink("/sem_check");
	sem_unlink("/sem_fork");
	sem_unlink("/sem_meal");
	if (tab->list)
		free(tab->list);
	tab->list = NULL;
}