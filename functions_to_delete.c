/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_to_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:26:00 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/24 19:24:35 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_permutation(int items [], int size, int l)
{
	 int i;
	 if (l==size)
	 {
		 for (i = 0; i < size; i++)
		   printf("%d ", items[i]);  
		 putchar('\n');
	 }
	 else
		 for (i = l; i < size; i++)
		 {
			 if (l^i)
			 {
				  items[l] ^= items[i];
				  items[i] ^= items[l];
				  items[l] ^= items[i];
				  get_permutation(items, size, l + 1);
				  items[l] ^= items[i];
				  items[i] ^= items[l];
				  items[l] ^= items[i];
			 }
			 else
				 get_permutation(items, size, l + 1);
		 }
}

void	print_figure(t_figure *figure)
{
	for (int i = 0; i < figure->size; i++)
		printf("%d%d ", figure->points[i]->x, figure->points[i]->y);
	printf("\n");
}

int		spare_main(int argc, char **argv)
{
	int			fd;
	int			figure_amount;
	int			empty_space_amount;
	int			square_size;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd != -1)
		{
			figure_amount = read_figures(fd);
			square_size = find_min_square_size(figure_amount * 4);
			empty_space_amount = square_size * square_size - figure_amount * 4;
			if (g_figs)
				printf("OK\n");
			else
				printf("error\n");
		}
	}
	return (0);
}

void	print_square(t_square *square)
{
	int i;
	
	i = 0;
	while (i < square->size)
	{
		print_bits(square->field[i], square->size);
		i++;
	}
}

void	print_bits(unsigned long long int data, int size)
{
	unsigned long long int   mask;
	
	mask = 0b1000000000000000000000000000000000000000000000000000000000000000;
	while (mask && size) {
		printf("%u", data & mask ? 1 : 0);
		mask >>= 1;
		size--;	   
	}
	printf("\n");
}
