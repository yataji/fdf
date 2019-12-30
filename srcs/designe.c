/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:24:01 by yataji            #+#    #+#             */
/*   Updated: 2019/12/29 12:05:34 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		iso(int *x, int *y, int z)
{
	int		previous_x;
	int		previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void		pixel(t_mlx mlx, t_point start, t_point end)
{
	mlx.iso ? iso(&start.x, &start.y, start.z) : 0;
	mlx.iso ? iso(&end.x, &end.y, end.z) : 0;
	mlx.math.dx = abs(end.x - start.x);
	mlx.math.dy = -abs(end.y - start.y);
	mlx.math.sx = end.x - start.x > 0 ? 1 : -1;
	mlx.math.sy = end.y - start.y > 0 ? 1 : -1;
	mlx.math.dp = 2 * mlx.math.dx + 2 * mlx.math.dy;
	while (start.x != end.x || start.y != end.y)
	{
		mlx_pixel_put(mlx.init, mlx.win, start.x + mlx.x0, start.y + mlx.y0,\
				start.c < end.c ? start.c : end.c);
		if (mlx.math.dp >= mlx.math.dy && start.x != end.x)
		{
			mlx.math.dp += mlx.math.dy;
			start.x += mlx.math.sx;
		}
		if (mlx.math.dp <= mlx.math.dx && start.y != end.y)
		{
			mlx.math.dp += mlx.math.dx;
			start.y += mlx.math.sy;
		}
	}
}

void		nextindex(t_point *start, t_point *end, t_mlx *mlx, t_tabcord **map)
{
	if (mlx->i < mlx->mcln - 1)
	{
		end->x = (*map)->save[mlx->i + 1].cln * mlx->zoom;
		end->y = (*map)->save[mlx->i + 1].line * mlx->zoom;
		end->z = (*map)->save[mlx->i + 1].height * mlx->h;
		end->c = (*map)->save[mlx->i + 1].clr + mlx->color;
		pixel(*mlx, *start, *end);
	}
	if ((*map)->next)
	{
		end->x = (*map)->next->save[mlx->i].cln * mlx->zoom;
		end->y = (*map)->next->save[mlx->i].line * mlx->zoom;
		end->z = (*map)->next->save[mlx->i].height * mlx->h;
		end->c = (*map)->next->save[mlx->i].clr + mlx->color;
		pixel(*mlx, *start, *end);
	}
}

int			indexpoint(t_mlx mlx)
{
	int			isoc;
	t_tabcord	*map;
	t_point		start;
	t_point		end;

	isoc = mlx.iso ? 0 : 1;
	mlx.menu = -1;
	mlx.x0 = ((mlx.win_cln - isoc * mlx.mcln * mlx.zoom) / 2) + mlx.movex;
	mlx.y0 = ((mlx.win_line - mlx.mln * mlx.zoom) / 2) + mlx.movey;
	map = mlx.dn;
	while (map)
	{
		mlx.i = -1;
		while (++mlx.i < mlx.mcln)
		{
			start.x = map->save[mlx.i].cln * mlx.zoom;
			start.y = map->save[mlx.i].line * mlx.zoom;
			start.z = map->save[mlx.i].height * mlx.h;
			start.c = map->save[mlx.i].clr + mlx.color;
			nextindex(&start, &end, &mlx, &map);
		}
		map = map->next;
	}
	menu(mlx);
	return (1);
}

void		designe(t_mlx *mlx)
{
	mlx->movey = 0;
	mlx->movex = 0;
	mlx->color = 0;
	mlx->h = 1;
	mlx->iso = 0;
	mlx->zoom = calculzoom(mlx);
	mlx->win_cln = mlx->mcln * 3 / 2 * mlx->zoom < MINCLN ? MINCLN : mlx->mcln\
					* 3 / 2 * mlx->zoom;
	mlx->win_line = mlx->mln * 3 / 2 * mlx->zoom < MINLN ? MINLN : mlx->mln\
					* 3 / 2 * mlx->zoom;
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, mlx->win_cln, mlx->win_line, mlx->av);
	indexpoint(*mlx);
	mlx_hook(mlx->win, 2, 0, &keypress, mlx);
	mlx_loop(mlx->init);
}
