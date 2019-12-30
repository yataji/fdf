/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:26:08 by yataji            #+#    #+#             */
/*   Updated: 2019/12/29 12:33:24 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include "../libft/libft.h"
# include <math.h>
# define MINLN 900
# define MINCLN 900
# define MAXCLN 3200
# define MAXLN 1755

typedef struct			s_point
{
	int					x;
	int					y;
	int					c;
	int					z;
}						t_point;

typedef struct			s_cord
{
	int					cln;
	int					line;
	int					height;
	int					clr;
}						t_cord;

typedef struct			s_tabcord
{
	t_cord				*save;
	struct s_tabcord	*next;
}						t_tabcord;

typedef struct			s_math
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					dp;
}						t_math;

typedef struct			s_mlx
{
	void				*init;
	void				*win;
	int					movex;
	int					movey;
	int					mln;
	int					mcln;
	int					x0;
	int					y0;
	int					zoom;
	int					color;
	int					h;
	int					i;
	char				*av;
	int					iso;
	int					win_cln;
	int					win_line;
	int					menu;
	t_tabcord			*dn;
	t_math				math;
}						t_mlx;

void					errormain(int fd, char *av);
int						check(int fd, t_mlx *mlx);
void					ft_exit(t_mlx *mlx);
int						err(char ***str, char **ln);
int						checklnmx(char **str);
int						strlen2dm(char **str);
t_tabcord				*save(char **str, int line, int dm, int *cln);
void					designe(t_mlx *mlx);
int						calculzoom(t_mlx *mlx);
int						indexpoint(t_mlx mlx);
void					nextindex(t_point *start, t_point *end, t_mlx *mlx,
		t_tabcord **map);
void					pixel(t_mlx mlx, t_point start, t_point end);
void					iso(int *x, int *y, int z);
void					menu(t_mlx mlx);
int						keypress(int key, t_mlx *param);
void					clear_tab(char **str);
int						clear_list(t_tabcord **donne);

#endif
