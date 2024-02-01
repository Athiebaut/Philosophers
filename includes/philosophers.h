/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:06:39 by athiebau          #+#    #+#             */
/*   Updated: 2024/01/24 16:59:26 by athiebau         ###   ########.fr       */
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
	size_t	time;
	t_chain		*list;
	
}		t_philo;

// typedef struct s_chain
// {
// 	int	index;
// 	int	nb_lunch;
// 	pthread_mutex_t	fork;
// 	t_philo		*tab;
// 	t_chain		*next;
// 	t_chain		*previous;
	
// }		t_chain;

#endif 
