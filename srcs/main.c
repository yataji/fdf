/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:31:57 by yataji            #+#    #+#             */
/*   Updated: 2019/12/02 12:32:10 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		err(char ***str, char **ln)
{
	if ((*ln)[0] == '\0')
	{
		free(*ln);
		ft_putendl("no data found");
		return (-1);
	}
	clear_tab(*str);
	free(*ln);
	ft_putendl("Found wrong line length. Exiting.");
	return (-1);
}

void	errormain(int fd, char *av)
{
	if (fd == -1)
	{
		ft_putstr("No file ");
		ft_putstr(av);
		ft_putchar('\n');
		return ;
	}
}

int		main(int ac, char **av)
{
	int			fd;
	int			dm;
	t_mlx		mlx;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDWR)) <= 0)
		{
			errormain(fd, av[1]);
			return (0);
		}
		if ((dm = check(fd, &mlx) == -1))
			return (clear_list(&mlx.dn));
	}
	else
	{
		ft_putendl("Usage : ./fdf <filename> [ case_size z_size ]");
		return (0);
	}
	mlx.av = av[1];
	designe(&mlx);
	clear_list(&mlx.dn);
	return (0);
}
