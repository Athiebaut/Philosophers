/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:53:44 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/26 02:05:51 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	*check_death_and_satiety(void *arg)
{
	t_philo	*philo;
	t_data	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	while (1)
	{
		sem_wait(tab->check);
		if ((get_time() - philo->last_meal > (size_t)tab->time_to_die) && tab->nb_philo != 1)
		{
			print_message(philo, M_DEATH);
			tab->dead = 1;
			exit (1);
		}
		sem_post(tab->check);
		if (tab->dead)
			break ;
		if (tab->nb_meals != -1 && philo->nb_meals >= tab->nb_meals)
			break ;
		usleep(1);
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
	sem_unlink("/sem_print");
	sem_unlink("/sem_check");
	sem_unlink("/sem_fork");
	free(tab->list);
	tab->list = NULL;
}