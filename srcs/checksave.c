/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 02:23:39 by yataji            #+#    #+#             */
/*   Updated: 2019/12/23 04:05:34 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				strlen2dm(char **str)
{
	int		i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int				checklnmx(char **str)
{
	static int	v;
	static int	dm;
	int			k;

	if (v == 0)
	{
		v++;
		dm = strlen2dm(str);
	}
	else
	{
		k = strlen2dm(str);
		if (k >= dm)
			return (dm);
		else
			return (-1);
	}
	return (dm);
}

t_tabcord		*save(char **str, int line, int dm, int *cln)
{
	int			i;
	char		*color;
	t_tabcord	*new;
	int			c;
	int			z;

	i = -1;
	if (!(new = (t_tabcord *)ft_memalloc(sizeof(t_tabcord))) ||\
			!(new->save = (t_cord *)ft_memalloc(sizeof(t_cord) * dm)))
		return (NULL);
	while (str && str[++i] && i < dm)
	{
		new->save[i].cln = i;
		new->save[i].line = line;
		new->save[i].height = ft_atoi(str[i]);
		color = ft_strchr(str[i], ',');
		c = color ? ft_atoi_base(color + 3, "0123456789ABCDEF") : 0;
		z = new->save[i].height ? new->save[i].height : 1;
		z = abs(z) > 0xFFFFFF || z == 1 ? z / 2 + 1 : abs(z) * 20;
		new->save[i].clr = c ? c : 0xFFFFFF / abs(z);
	}
	*cln = i;
	return (new);
}

int				check(int fd, t_mlx *mlx)
{
	char		**str;
	char		*ln;
	int			dm;
	int			line;
	t_tabcord	*tmp;

	line = 0;
	while (get_next_line(fd, &ln) > 0 && (str = ft_strsplit(ln, ' ')))
	{
		if (ln[0] == '\0')
			return (err(&str, &ln));
		if ((dm = checklnmx(str)) == -1)
			return (err(&str, &ln));
		if (!mlx->dn && (mlx->dn = save(str, line++, dm, &mlx->mcln)))
			tmp = mlx->dn;
		else if ((tmp->next = save(str, line++, dm, &mlx->mcln)))
			tmp = tmp->next;
		free(ln);
		ln = NULL;
		clear_tab(str);
	}
	mlx->mln = line;
	free(ln);
	return (dm);
}
