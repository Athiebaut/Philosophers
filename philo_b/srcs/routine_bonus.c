/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:57:58 by vleida            #+#    #+#             */
/*   Updated: 2024/03/28 06:08:15 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	check_death(t_philo *philo)
{
	long	time;

	time = get_time();
	if (time - philo->last_meal > philo->tab->time_to_die)
	{
		philo->state = 1;
		time = time - philo->startime_to_eat;
		sem_wait(philo->tab->print);
		printf("%ld %d died\n", time, philo->index);
		ft_free_all(philo->tab);
		return(1);
	}
	return (0);
}

static int	take_forks(t_philo *philo)
{
	sem_wait(philo->tab->forks);
	print_message("%ld %d has taken a fork\n", philo);
	if (philo->tab->nb_philo == 1)
	{
		ft_usleep(philo->tab->time_to_die + 1, philo);
		sem_post(philo->tab->forks);
		return (0);
	}
	else
	{
		if (check_death(philo))
			return (0);
		sem_wait(philo->tab->forks);
		print_message("%ld %d has taken a fork\n", philo);
	}
	return (1);
}

static void	meal_philo(t_philo *philo)
{
	if (philo->tab->exception && philo->index == philo->tab->nb_philo
		&& philo->tab->nb_philo != 1)
		ft_usleep(philo->tab->time_to_die + 1, philo);
	if (take_forks(philo))
	{
		philo->nb_meals++;
		print_message("%ld %d is eating\n", philo);
		ft_usleep(philo->tab->time_to_eat, philo);
		sem_post(philo->tab->forks);
		sem_post(philo->tab->forks);
		if (check_death(philo))
			return ;
		philo->last_meal = get_time();
		if (philo->nb_meals == philo->tab->nb_meals_total)
		{
			sem_close(philo->tab->print);
			ft_free_all(philo->tab);
			exit(2);
		}
	}
}

static void	other_actions(t_philo *philo)
{
	int	time;

	print_message("%ld %d is sleeping\n", philo);
	ft_usleep(philo->tab->time_to_sleep, philo);
	if (check_death(philo))
		return ;
	print_message("%ld %d is thinking\n", philo);
	if (philo->tab->time_to_eat > philo->tab->time_to_sleep)
	{
		time = philo->tab->time_to_eat - philo->tab->time_to_sleep - 1;
		ft_usleep(time, philo);
	}
}

void	routine(t_philo	*philo)
{
	philo->last_meal = philo->startime_to_eat;
	if (philo->index > (philo->tab->nb_philo / 2) + 1)
		usleep(20000);
	while (!philo->state)
	{
		if (!philo->state)
			meal_philo(philo);
		if (!philo->state)
			other_actions(philo);
		if (!philo->state)
			usleep(TT_SLEEP);
	}
}
