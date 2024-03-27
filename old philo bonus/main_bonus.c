/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:17:57 by alix              #+#    #+#             */
/*   Updated: 2024/03/27 04:19:19 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	ft_error(int error, t_data *tab)
{
	(void)tab;
	if (error == E_PARSING)
		printf("Error: Invalids parameters\n");
	else
		perror("Error:");
	if (tab->list)
	{
		free(tab->list);
		tab->list = NULL;
	}
	exit(1);
}

int	main(int ac, char **av)
{
	t_data		tab;
	int	i;
	
	if (ac < 5 || ac > 6 || check_args(av, &tab) == 1)
		ft_error(E_PARSING, NULL);
	tab.time_0 = get_time();
	if (tab.time_0 == -1)
		ft_error(E_TIME, &tab);
	i = -1;
	while (++i < tab.nb_philo)
	{
		tab.list[i].pid = fork();
		if (tab.list[i].pid == -1)
			ft_error(E_FORK, &tab);
		if (tab.list[i].pid == 0)
			routine(&tab.list[i]);
	}
	the_end(&tab);
	return (0);
}