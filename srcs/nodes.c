/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

static void     get_neighbourdata(t_pf *data, int x, int y, int pos)
{
    t_node  *nodes;

    nodes = data->list;
	nodes[pos].ngbhr[0] = NULL;
	nodes[pos].ngbhr[1] = NULL;
	nodes[pos].ngbhr[2] = NULL;
	nodes[pos].ngbhr[3] = NULL;
    if (y > 0)
        nodes[pos].ngbhr[0] = &nodes[(y - 1) * data->mw + x];
    if (y < data->mh - 1)
        nodes[pos].ngbhr[1] = &nodes[(y + 1) * data->mw + x];
    if (x > 0)
        nodes[pos].ngbhr[2] = &nodes[y * data->mw + (x - 1)];
    if (x < data->mw - 1)
        nodes[pos].ngbhr[3] = &nodes[y * data->mw + (x + 1)];
}

void            get_nodes(t_pf *data)
{
    int     x;
    int     y;
    int     pos;

    if (!(data->list = (t_node *)ft_memalloc(sizeof(t_node) * (data->mlen))))
        clean_exit(data, "malloc error", 0);
    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
        {
            pos = y * data->mw + x;
            data->list[pos].i = pos;
            data->list[pos].x = x;
            data->list[pos].y = y;
            get_neighbourdata(data, x, y, pos);
        }
    }
}
