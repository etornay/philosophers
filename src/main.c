/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:13:52 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/19 14:13:14 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (checker(argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		printf("Bonito todo\n");
	}
	return (EXIT_SUCCESS);
}
