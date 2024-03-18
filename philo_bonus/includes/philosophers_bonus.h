/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:06:39 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/18 01:14:11 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../Libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h> 

/*
 ----------------------------------------
|		STRUCTURES		 |
 ----------------------------------------
*/

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				index;
	int				nb_meals;
	size_t			last_meal;
	t_philo			*next;
	t_data			*tab;
	pid_t			pid;
	pthread_t		death_satiety;

}						t_philo;

typedef struct s_data
{
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long long		time_to_think;
	int				nb_meals;
	int				dead;
	int				satiety;
	long long		time_0;
	sem_t 		*check;
	sem_t		*print;
	sem_t		*meal;
	sem_t		*fork;
	t_philo			*list;

}						t_data;

/*
 ----------------------------------------
|		   ENUM		 	 |
 ----------------------------------------
*/

enum
{
	E_PARSING,
	E_FORK,
	E_SEMAPHORE,
	E_TIME,
	E_MALLOC,
};

enum
{
	M_FORK,
	M_DEATH,
	M_EAT,
	M_SLEEP,
	M_THINK,
	M_DROP
};

/*
 ----------------------------------------
|		   FILES		 |
 ----------------------------------------
*/

#endif
