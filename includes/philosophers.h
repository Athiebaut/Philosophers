/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:06:39 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/08 15:15:31 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

//#include "macro.h"
#include "../Libft/libft.h"

#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

/*
 ----------------------------------------
|		STRUCTURES	         |
 ----------------------------------------
*/

typedef struct s_philo t_philo;
typedef struct s_chain t_chain;

typedef struct s_chain
{
	int	index;
	int	nb_repas;
	pthread_mutex_t	fourchette;
	t_philo		*tab;
	t_chain		*suivant;
	t_chain		*precedent;
	
}		t_chain;

typedef struct s_philo
{
	int	nb_philo;
	int	temps_pour_mourir;
	int	temps_pour_manger;
	int	temps_pour_dormir;
	int	nb_repas;
	int	mort;
	long long	temps;
	pthread_mutex_t	check;
	t_chain		*liste;
	
}		t_philo;

/*
 ----------------------------------------
|		   ENUM	                 |
 ----------------------------------------
*/

enum
{
	E_PARSING,
	E_TCREATE,
	E_TIME,
};

enum
{
	M_FOURCHETTE,
	M_MORT,
	M_MANGER,
	M_DORMIR,
	M_PENSER,	
};

/*
 ----------------------------------------
|		   MACROS	         |
 ----------------------------------------
*/

#define tant_que(value) while(value)
#define si(value) if(value)
#define sinon else
#define retour(value) return(value)
#define sortie(value) exit(value)
#define taille_de(value) sizeof(value)
#define liberation(value) free(value)

/*
 ----------------------------------------
|		   FILES	         |
 ----------------------------------------
*/

int	ft_verifier_arguments(char **av, t_philo *tab);

void	ft_erreur(int erreur);
size_t	recuperer_temps_actuel(void);

#endif 
