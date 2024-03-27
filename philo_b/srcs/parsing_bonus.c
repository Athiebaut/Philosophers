/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:35:24 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/27 21:35:34 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (digits_check(argv[i]))
			return (print_msg("Invalid input\n", 1));
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb > 200 || nb <= 0))
			return (print_msg("Invalid nb of philos\n", 1));
		if (i != 1 && nb == -1)
			return (print_msg("Invalid input\n", 1));
		i++;
	}
	return (0);
}

int	digits_check(char *s)
{
	int	i;

	if (!s || !s[0])
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *s)
{
	unsigned long long int	n;
	int						i;

	n = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	if (n > 2147483647)
		return (-1);
	return ((int) n);
}