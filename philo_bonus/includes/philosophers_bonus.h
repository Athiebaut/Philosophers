/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:57:51 by vleida            #+#    #+#             */
/*   Updated: 2024/03/28 05:43:48 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>

# define MX_INT		2147483647
# define MN_INT		-2147483648
# define TT_SLEEP	100

/*
 ----------------------------------------
|		STRUCTURES		 |
 ----------------------------------------
*/

typedef struct s_philo
{
	int				index;
	int				fl;
	int				state;
	int				nb_meals;
	long			last_meal;
	long			startime_to_eat;
	struct s_tab	*tab;
}				t_philo;

typedef struct s_tab
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_total;
	int				nb_full;
	int				dead;
	int				error_fl;
	int				exception;
	long			time_0;
	t_philo			*philo;
	pid_t			*pid_all;
	sem_t			*forks;
	sem_t			*print;
}			t_tab;

/*
 ----------------------------------------
|			FILES		 |
 ----------------------------------------
*/

long	get_time(void);
void	ft_usleep(int time_ms, t_philo *philo);
void	ft_free_all(t_tab	*tab);
void	print_message(char *str, t_philo *philo);

void	init_tab(char **av, t_tab *tab, int ac);

void	routine(t_philo	*philo);

#endif
