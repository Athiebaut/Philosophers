/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:06:39 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/18 00:21:13 by alix             ###   ########.fr       */
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
	int				meals_nb;
	size_t			last_meal;
	pthread_mutex_t	fork;
	t_data			*tab;
	t_philo			*next;

}						t_philo;

typedef struct s_data
{
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long long		time_to_think;
	int				meals_nb;
	int				dead;
	int				satiety;
	long long		time_0;
	pthread_t	*id;
	pthread_mutex_t	check;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	t_philo			*list;

}						t_data;

/*
 ----------------------------------------
|		    ENUM		 |
 ----------------------------------------
*/

enum
{
	E_MUTEX,
	E_PARSING,
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

int		check_args(char **av, t_data *tab);

void	*routine(void *arg);

void	ft_error(int erreur, t_data *tab);

size_t	get_time(void);
void	spend_time(t_data *tab, size_t time);
void	print_message(t_philo *philo, int message);

bool	is_philo_dead(t_data *tab);

bool	test_death(t_data *tab);
bool	test_satiety(t_data *tab);
void	check_death_and_satiety(t_data *tab);

#endif
