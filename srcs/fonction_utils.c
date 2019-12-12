/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 04:25:22 by yataji            #+#    #+#             */
/*   Updated: 2019/12/11 19:52:34 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		clear_list(t_tabcord **donne)
{
	t_tabcord	*tmp;

	while (donne && *donne)
	{
		tmp = (*donne)->next;
		free((*donne)->save);
		free(*donne);
		*donne = tmp;
	}
	return (-1);
}

void	clear_tab(char **str)
{
	int			i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

int		keypress(int key, t_mlx *param)
{
	if (param)
	{
		key == 53 ? exit(0) : 0;
		key == 69 ? param->zoom++ : 0;
		key == 78 && param->zoom > 1 ? param->zoom-- : 0;
		key == 4 ? param->h++ : 0;
		key == 37 ? param->h-- : 0;
		key == 34 ? param->iso = 1 : 0;
		key == 35 ? param->iso = 0 : 0;
		key == 116 ? param->color += 10 : 0;
		key == 121 ? param->color -= 10 : 0;
		key == 15 ? param->color = 0 : 0;
		key == 126 ? param->movey -= 10 : 0;
		key == 125 ? param->movey += 10 : 0;
		key == 124 ? param->movex += 10 : 0;
		key == 123 ? param->movex -= 10 : 0;
		mlx_clear_window(param->init, param->win);
		indexpoint(*param);
	}
	return (1);
}

int		calculzoom(t_mlx *mlx)
{
	int		zoom;

	zoom = 40;
	while ((MAXCLN < mlx->mcln * 3 / 2 * zoom ||\
				MAXLN < mlx->mln * 3 / 2 * zoom) && zoom > 1)
		zoom--;
	return (zoom);
}

void	menu(t_mlx fdf)
{
	fdf.menu = -1;
	while (++fdf.menu < 251)
	{
		mlx_pixel_put(fdf.init, fdf.win, fdf.menu, fdf.win_line - 220, 0xFF);
		mlx_pixel_put(fdf.init, fdf.win, fdf.menu, fdf.win_line - 250, 0xFF);
	}
	fdf.menu = fdf.win_line - 250;
	while (++fdf.menu < fdf.win_line)
		mlx_pixel_put(fdf.init, fdf.win, 250, fdf.menu, 0xFF);
	mlx_string_put(fdf.init, fdf.win, 100, fdf.win_line - 250, 0x00FF00,
			"MENU:");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 200,\
			0x00FF00, "ISO PROJECTION: I");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 170,\
			0x00FF00, "PARALLEL PROJECTION: P");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 140,\
			0x00FF00, "MOVE with ARROWS");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 110,\
			0x00FF00, "ZOOM : + / -");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 80,\
			0x00FF00, "ALTITUDE H / L");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 50,\
			0x00FF00, "COLORS: PAGEUP PAGEDOWN");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_line - 30,\
			0x00FF00, "              R");
}
