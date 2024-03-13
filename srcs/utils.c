/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:21:46 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/13 20:05:20 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_error(int error)
{
	if (error == E_PARSING)
		printf("Error: Invalids parameters\n");
	if (error == E_TCREATE || error == E_TIME)
		perror("Error:");
	exit(1);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	spend_time(t_data *tab, size_t time)
{
	size_t	t;
	int	flag;

	flag = 0;
	t = get_time();
	while (!(tab->dead))
	{
		if (get_time() - t >= time)
		{
			flag = 1;
			break ;
		}
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
	size_t	time;

	pthread_mutex_lock(&philo->tab->print);
	pthread_mutex_lock(&philo->tab->check);
	time = get_time() - philo->tab->time_0;
	if (!philo->tab->dead && !philo->tab->satiety)
	{
		printf("-%ld ", time);
		printf("%d ", philo->index);
		printf("%s\n", get_message(message));
	}
	pthread_mutex_unlock(&philo->tab->print);
	pthread_mutex_unlock(&philo->tab->check);
}
