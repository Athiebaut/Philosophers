/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:06:39 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/27 04:07:00 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../../Libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/wait.h>
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
	//int				satiety;
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
	E_THREAD,
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

void	ft_error(int error, t_data *tab);

int	check_args(char **av, t_data *tab);

bool	test_meals(t_philo *philo);
bool	test_death(t_data *tab);
void	*check_death_and_satiety(void *arg);
void	the_end(t_data *tab);

void	*routine(void *arg);

void	spend_time(t_philo *philo, long long time);
long long	get_time(void);
void	print_message(t_philo *philo, int message);

#endif
