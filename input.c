/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:52:48 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/24 20:49:00 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_point_in_points(t_point *point, t_point **points)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (are_points_equal(point, points[i]))
			return (1);
		i++;
	}
	return (0);
}

int		count_point_connections(t_point *point, t_point **points)
{
	return ((is_point_in_points(create_point(point->x, point->y - 1), points)
		+ is_point_in_points(create_point(point->x, point->y + 1), points)
		+ is_point_in_points(create_point(point->x - 1, point->y), points)
		+ is_point_in_points(create_point(point->x + 1, point->y), points)));
}

int		are_points_tetrimino(t_point **points)
{
	int connections;
	int i;

	connections = 0;
	i = 0;
	while (i < 4)
	{
		connections += count_point_connections(points[i], points);
		i++;
	}
	if ((connections == 6) || (connections == 8))
		return (1);
	return (0);
}

t_point	**get_initial_figure_points(t_point **points)
{
	int x_shift;
	int y_shift;
	int i;

	x_shift = points[0]->x;
	y_shift = points[0]->y;
	i = 0;
	while (i < 4)
	{
		points[i]->x -= x_shift;
		points[i]->y -= y_shift;
		i++;
	}
	return (points);
}

int		something_went_wrong(int i, char *temp_figure, int temp_figure_size)
{
	return (
		((i % 5 != 4) && (i != 20) && (temp_figure[i] != '.') && (temp_figure[i] != '#'))
		|| ((i % 5 == 4) && (temp_figure[i] != '\n'))
		|| ((i == 20) && (temp_figure[i] != '\n') && (temp_figure[i] != 0))
		|| (temp_figure_size > 4)
		);
}

t_point	**get_figure_points(char *temp_figure, int figure_number)
{
	t_point	**points;
	int		temp_figure_size;
	int		i;

	points = (t_point **)malloc(sizeof(t_point *) * 4);
	temp_figure_size = 0;
	i = 0;
	while (i < 21)
	{
		if (something_went_wrong(i, temp_figure, temp_figure_size))
			exit(print_error());
		if (temp_figure[i] == '#')
		{
			*points++ = create_point(i / 5, i % 5);
			temp_figure_size++;
		}
		i++;
	}
	if (temp_figure_size != 4)
		exit(print_error());
	if (are_points_tetrimino(points - 4))
		return (get_initial_figure_points(points - 4));
	exit(print_error());
}

// void	null_temp_figure(char *temp_figure)
// {
// 	int i;

// 	i = 0;
// 	while (i < 21)
// 	{
// 		temp_figure[i] = 0;
// 		i++;
// 	}
// }

int		read_figures(int fd)
{
	int			i;
	char		temp_figure[22];
	char		anna_sobachka;
	t_point		**figure_points;
	int			figure_amount;

	i = 0;
	ft_bzero(temp_figure, 22);
	while (read(fd, temp_figure, 21))
	{
		anna_sobachka = temp_figure[20];		
		figure_points = get_figure_points(temp_figure, i);
		ft_bzero(temp_figure, 22);
		g_figs[i] = create_figure(figure_points, 4);
		i++;
	}
	if (!i || anna_sobachka != 0)
		exit(print_error());
	return (i);
}
