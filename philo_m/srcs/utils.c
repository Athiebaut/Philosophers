/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:21:46 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/27 02:07:42 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	spend_time(t_data *tab, size_t time)
{
	size_t	t;

	t = get_time();
	while (!test_death(tab))
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

bool	is_philo_dead(t_data *tab)
{
	if (test_death(tab) || test_satiety(tab))
		return (true);
	return (false);
}

void	print_message(t_philo *philo, int message)
{
	size_t	time;
	bool	res;

	time = get_time() - philo->tab->time_0;
	if (pthread_mutex_lock(&philo->tab->print))
		ft_error(E_MUTEX, philo->tab);
	res = is_philo_dead(philo->tab);
	if (!res || message == M_DEATH)
		printf("%ld %d %s\n", time, philo->index, get_message(message));
	if (pthread_mutex_unlock(&philo->tab->print))
		ft_error(E_MUTEX, philo->tab);
}
