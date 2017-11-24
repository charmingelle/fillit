/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:47:52 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/24 20:25:05 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_figure
{
	int		size;
	t_point **points;
}				t_figure;

typedef struct	s_square
{
	unsigned long long int	*field;
	int						size;
}				t_square;

t_figure		**g_figs;
t_figure		*g_empty_figure;
int				*g_inds;
t_square		*g_square;
char			**g_result;

int				find_min_square_size(int figure_square);
t_point			*create_point(int x, int y);
int				are_points_equal(t_point *a, t_point *b);
t_figure		*create_figure(t_point **points, int size);
void			print_bits(unsigned long long int data, int size);
void			place_bit(unsigned long long int *row, int number);
void			set_coord(t_point *point);
int				is_bit_placed(t_point *point);
int				is_point_on_square(t_point *point);
int				figure_fits(t_point *point, t_figure *figure);
int				empty_space_fits(t_point *empty);
void			place_figure(t_point *point, t_figure *figure);
void			initiate_square(int size);
void			free_square(void);
void			set_square_to_zero(t_square *square);
t_point			*get_first_empty(void);
void			get_permutations(int amount, int l);
void			process_permutation(int amount);
int				count_figures(int fd);
int				is_point_in_points(t_point *point, t_point **points);
int				count_point_connections(t_point *point, t_point **points);
int				are_points_tetrimino(t_point **points);
t_point			**get_initial_figure_points(t_point **points);
int				something_went_wrong(int i, char *temp_figure,
	int temp_figure_size);
t_point			**get_figure_points(char *temp_figure, int figure_number);
void			null_temp_figure(char *temp_figure);
int				read_figures(int fd);
void			initiate_result(int size);
void			free_result(int size);
void			null_result(int size);
int				print_result(int size);
void			add_figure_to_result(t_point *empty, t_figure *figure,
	char symbol);
void			initiate_index_array(int figure_amount, int empty_space_amount);
int				print_error(void);
void			ft_bzero(void *s, size_t n);

void			get_permutation(int items[], int size, int l);
void			print_figure(t_figure *figure);
int				spare_main(int argc, char **argv);
void			print_square(t_square *square);

#endif
