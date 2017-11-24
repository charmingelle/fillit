/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:53:34 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/24 19:24:56 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			find_min_square_size(int figure_square)
{
	int odd;
	int base;
	int square;

	odd = 3;
	base = 1;
	square = 1;
	while (square < figure_square)
	{
		base++;
		square += odd;
		odd += 2;
	}
	return (base);
}

t_point		*create_point(int x, int y)
{
	t_point *new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	return (new);
}

int			are_points_equal(t_point *a, t_point *b)
{
	return ((a->x == b->x) && (a->y == b->y));
}

t_figure	*create_figure(t_point **points, int size)
{
	t_figure *new;

	new = (t_figure *)malloc(sizeof(t_figure));
	new->size = size;
	new->points = points;
	return (new);
}

void		place_bit(unsigned long long int *row, int number)
{
	unsigned long long int mask;

	mask = 1L << 63;
	mask >>= number;
	*row |= mask;
}

void		set_coord(t_point *point)
{
	place_bit(&(g_square->field[point->x]), point->y);
}

int			is_bit_placed(t_point *point)
{
	unsigned long long int mask;

	mask = 1L << 63;
	mask >>= point->y;
	if (!(g_square->field[point->x] & mask))
		return (0);
	return (1);
}

int			is_point_on_square(t_point *point)
{
	return ((point->x >= 0) && (point->x < g_square->size) && (point->y >= 0)
		&& (point->y < g_square->size));
}

int			figure_fits(t_point *point, t_figure *figure)
{
	int		i;
	t_point	*temp_point;

	i = 0;
	while (i < figure->size)
	{
		temp_point = create_point(figure->points[i]->x + point->x,
			figure->points[i]->y + point->y);
		if (!is_point_on_square(temp_point) || is_bit_placed(temp_point))
		{
			free(temp_point);
			return (0);
		}
		else
			free(temp_point);
		i++;
	}
	return (1);
}

int			empty_space_fits(t_point *empty)
{
	return (is_point_on_square(empty) && !is_bit_placed(empty));
}

void		place_figure(t_point *point, t_figure *figure)
{
	int		i;
	t_point	*temp_point;

	i = 0;
	while (i < figure->size)
	{
		temp_point = create_point(point->x + figure->points[i]->x,
			point->y + figure->points[i]->y);
		set_coord(temp_point);
		free(temp_point);
		i++;
	}
}

void		initiate_square(int size)
{
	int i;

	g_square = (t_square *)malloc(sizeof(t_square));
	g_square->field = (unsigned long long int *)
	malloc(sizeof(unsigned long long int) * 64);
	i = 0;
	while (i < 64)
	{
		g_square->field[i] = 0;
		i++;
	}
	g_square->size = size;
}

void		free_square(void)
{
	free(g_square->field);
	free(g_square);
}

void		set_square_to_zero(t_square *square)
{
	int i;

	i = 0;
	while (i < 64)
	{
		square->field[i] = 0;
		i++;
	}
}

t_point		*get_first_empty(void)
{
	t_point	*new;
	int		i;
	int		j;

	i = 0;
	while (i < g_square->size)
	{
		j = 0;
		while (j < g_square->size)
		{
			new = create_point(i, j);
			if (!is_bit_placed(new))
				return (new);
			free(new);
			j++;
		}
		i++;
	}
	new = create_point(-1, -1);
	return (new);
}

void		initiate_result(int size)
{
	int i;

	g_result = (char **)malloc(sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		g_result[i] = (char *)malloc(sizeof(char) * size);
		i++;
	}
}

void		free_result(int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(g_result[i]);
		i++;
	}
	free(g_result);
}

void		null_result(int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			g_result[i][j] = 0;
			j++;
		}
		i++;
	}
}

int			print_result(int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			write(1, &g_result[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int			print_error(void)
{
	write(1, "error\n", 6);
	return (1);
}

void		add_figure_to_result(t_point *empty, t_figure *figure, char symbol)
{
	int i;

	i = 0;
	while (i < figure->size)
	{
		g_result[empty->x + figure->points[i]->x][empty->y
			+ figure->points[i]->y] = symbol;
		i++;
	}
}

t_figure	*create_empty_figure(void)
{
	t_figure	*empty_figure;
	t_point		**points;

	empty_figure = (t_figure *)malloc(sizeof(t_figure));
	points = (t_point **)malloc(sizeof(t_point *));
	points[0] = create_point(0, 0);
	empty_figure->size = 1;
	empty_figure->points = points;
	return (empty_figure);
}

void		process_permutation(int amount)
{
	int		i;
	t_point	*empty;

	set_square_to_zero(g_square);
	i = -1;
	while (++i < amount)
	{
		empty = get_first_empty();
		if ((g_inds[i] != -1) && figure_fits(empty, g_figs[g_inds[i]]))
		{
			place_figure(empty, g_figs[g_inds[i]]);
			add_figure_to_result(empty, g_figs[g_inds[i]], g_inds[i] + 'A');
		}
		else if ((g_inds[i] == -1) && empty_space_fits(empty))
		{
			set_coord(empty);
			add_figure_to_result(empty, g_empty_figure, '.');
		}
		else
		{
			null_result(g_square->size);
			return ;
		}
	}
	exit(print_result(g_square->size));
}

void		get_permutations(int amount, int l)
{
	int i;

	if (l == amount)
		process_permutation(amount);
	else
	{
		i = l;
		while (i < amount)
		{
			if (l ^ i)
			{
				g_inds[l] ^= g_inds[i];
				g_inds[i] ^= g_inds[l];
				g_inds[l] ^= g_inds[i];
				get_permutations(amount, l + 1);
				g_inds[l] ^= g_inds[i];
				g_inds[i] ^= g_inds[l];
				g_inds[l] ^= g_inds[i];
			}
			else
				get_permutations(amount, l + 1);
			i++;
		}
	}
}

void		initiate_index_array(int figure_amount, int empty_space_amount)
{
	int i;

	g_inds = (int *)malloc(sizeof(int) * (figure_amount
		+ empty_space_amount));
	i = 0;
	while (i < figure_amount)
	{
		g_inds[i] = i;
		i++;
	}
	while (empty_space_amount)
	{
		g_inds[i++] = -1;
		empty_space_amount--;
	}
}

int			count_figures(int fd)
{
	char	previous;
	char	current;
	int		result;

	result = 0;
	previous = 0;
	while (read(fd, &current, 1))
	{
		if (previous != '\n' && current == '\n')
			result++;
		previous = current;
	}
	return (result / 4);
}

void		solve(int fd)
{
	int figure_amount;
	int empty_space_amount;
	int square_size;

	g_figs = (t_figure **)malloc(sizeof(t_figure *) * 26);
	figure_amount = read_figures(fd);
	square_size = find_min_square_size(figure_amount * 4);
	empty_space_amount = square_size * square_size - figure_amount * 4;
	while (1)
	{
		g_empty_figure = create_empty_figure();
		initiate_index_array(figure_amount, empty_space_amount);
		initiate_square(square_size);
		initiate_result(square_size);
		get_permutations(figure_amount + empty_space_amount, 0);
		free(g_inds);
		free_square();
		free_result(square_size);
		square_size++;
		empty_space_amount += (square_size * 2 - 1);
	}
}

int			main(int argc, char **argv)
{
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(print_error());
		solve(fd);
	}
	else
		write(1, "usage: ./fillit source_file\n", 28);
	return (0);
}
