/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:36:28 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/27 21:36:34 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

time_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	action_time(time_t sleep_duration, int i, t_cycle *cycle)
{
	time_t	end;

	end = get_time_ms() + sleep_duration;
	while (get_time_ms() <= end - 9)
	{
		send_flag(cycle, i);
		if (!am_i_dead(cycle, i) && !check_stop_flag(cycle))
			usleep(9000);
	}
	while (get_time_ms() < end)
	{
		send_flag(cycle, i);
		if (!am_i_dead(cycle, i) && !check_stop_flag(cycle))
			usleep(1000);
	}
	return (0);
}

int	am_i_dead(t_cycle *cycle, int i)
{
	(void)i;
	if (get_time_ms() - cycle->last_meal >= cycle->die_time)
		return (1);
	return (0);
}

int	send_flag(t_cycle *cycle, int i)
{
	if (get_time_ms() - cycle->last_meal >= cycle->die_time)
	{
		sem_wait(cycle->write);
		printf("%ld %d has died\n", get_time_ms() - cycle->start_time,
			i + 1);
		sem_post(cycle->dead);
		while (1)
			usleep(9000);
		return (1);
	}
	return (0);
}