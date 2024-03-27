/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:28:06 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/27 21:28:31 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo_bonus.h"

int	print_msg(char *s, int exit_no)
{
	printf("%s", s);
	return (exit_no);
}

void	*print_msg_null(char *s, t_cycle *cycle)
{
	if (cycle)
		free_cycle(cycle);
	print_msg(s, 1);
	return (NULL);
}

int	print_msg_err(char *s, t_cycle *cycle)
{
	if (cycle)
		free_cycle(cycle);
	return (print_msg(s, 1));
}

void	*free_cycle(t_cycle *cycle)
{
	if (!cycle)
		return (NULL);
	close_sems(cycle);
	unlink_sem(cycle);
	if (cycle->tabpid)
		free(cycle->tabpid);
	free(cycle);
	return (NULL);
}

void	unlink_sem(t_cycle *cycle)
{
	if (cycle)
	{
		sem_unlink(SFORKS);
		sem_unlink(SEAT);
		sem_unlink(SDEAD);
		sem_unlink(SWRITE);
		sem_unlink(SSTOP);
	}
}