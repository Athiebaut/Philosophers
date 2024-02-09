/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:06:39 by athiebau          #+#    #+#             */
/*   Updated: 2024/02/08 17:01:48 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
#include "../Libft/libft.h"
#include <sys/time.h>

#include <stdio.h>

typedef struct s_philo t_philo;
typedef struct s_chain t_chain;

typedef struct s_chain
{
	int	index;
	int	nb_lunch;
	pthread_mutex_t	fork;
	t_philo		*tab;
	t_chain		*next;
	t_chain		*previous;
	
}		t_chain;

typedef struct s_philo
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_lunch;
	int	death;
	long long	time;
	pthread_mutex_t	check;
	t_chain		*list;
	
}		t_philo;

enum
{
	E_PARSING,
	E_TCREATE,
	E_TIME,
};

int	check_args(char **av, t_philo *tab);

#endif 
