/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:46:50 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/26 02:09:48 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	spend_time(t_data *tab, size_t time)
{
	long long	t;

	t = get_time();
	if (t == -1)
		ft_error(E_TIME, tab);
	while (!tab->dead)
	{
		if (get_time() - t >= time)
			break ;
		usleep(100);
	}
}

static char	*get_message(int message)
{
	if (message == M_SLEEP)
		return ("is sleeping");
	if (message == M_FORK)
		return ("has taken a fork");
	if (message == M_EAT)
		return ("is eating");
	if (message == M_DEATH)
		return ("died");
	if (message == M_THINK)
		return ("is thinking");
	return ("Error: id msg not valid");
}

void	print_message(t_philo *philo, int message)
{
	size_t	t;

	t = get_time() - philo->tab->time_0;
	sem_wait(philo->tab->print);
	if (!philo->tab->dead && !philo->tab->satiety)
		printf("%ld %d %s\n", t, philo->index, get_message(message));
	sem_post(philo->tab->print);
}