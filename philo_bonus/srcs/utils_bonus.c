/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:57:48 by vleida            #+#    #+#             */
/*   Updated: 2024/03/28 06:09:05 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

long	get_time(void)
{
	struct timeval	tv;
	long			rez;

	gettimeofday(&tv, NULL);
	rez = (tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
	return (rez);
}

static void	spend_time(long ms, long start)
{
	start = start + ms;
	if (ms > 10)
		usleep ((ms - 10) * 1000);
	while (1)
	{
		if (start < get_time())
			return ;
		usleep(50);
	}
}

void	ft_usleep(int time_ms, t_philo *philo)
{
	long	life_time;
	long	real_time;

	life_time = philo->last_meal + philo->tab->time_to_die;
	real_time = get_time();
	if (real_time + time_ms > life_time)
	{
		life_time = life_time - real_time;
		spend_time(life_time, real_time);
		if (philo->state == 1)
			return ;
		life_time = get_time() - philo->startime_to_eat;
		sem_wait(philo->tab->print);
		printf("%ld %d died\n", life_time, philo->index);
		sem_close(philo->tab->print);
		ft_free_all(philo->tab);
		exit(1);
	}
	spend_time(time_ms, real_time);
}

void	ft_free_all(t_tab *tab)
{
	sem_close(tab->forks);
	free(tab->philo);
	free(tab->pid_all);
}

void	print_message(char *str, t_philo *philo)
{
	long	time;

	sem_wait(philo->tab->print);
	time = get_time() - philo->startime_to_eat;
	if (!philo->state)
		printf(str, time, philo->index);
	sem_post(philo->tab->print);
}
