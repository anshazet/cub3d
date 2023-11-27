/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:14:02 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/27 15:25:07 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main (int ac, char **av)
{
	(void)av;
	if (ac < 2)
		printf("Error: to few arguments\n");
	if (ac == 2)
		printf("welcome to cub3d\n");
	return (0);
}