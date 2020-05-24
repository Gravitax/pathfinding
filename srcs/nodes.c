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

static void     get_neighbourdata(t_pf *data, int x, int y)
{
    t_node  **nodes;

    nodes = data->list;
	nodes[x][y].ngbhr[0] = NULL;
	nodes[x][y].ngbhr[1] = NULL;
	nodes[x][y].ngbhr[2] = NULL;
	nodes[x][y].ngbhr[3] = NULL;
    if (y > 0)
        nodes[x][y].ngbhr[0] = &nodes[x][y - 1];
    if (y < data->mh - 1)
        nodes[x][y].ngbhr[1] = &nodes[x][y + 1];
    if (x > 0)
        nodes[x][y].ngbhr[2] = &nodes[x - 1][y];
    if (x < data->mw - 1)
        nodes[x][y].ngbhr[3] = &nodes[x + 1][y];
}

void            get_nodes(t_pf *data)
{
    int     x;
    int     y;

    if (!(data->list = (t_node **)ft_memalloc(sizeof(t_node *) * (data->mw))))
        clean_exit(data, "malloc error", 0);
    for (int i = 0; i < data->mw; i++)
    {
        if (!(data->list[i] = ft_memalloc(sizeof(t_node) * data->mh)))
            clean_exit(data, "malloc error", 0);
    }
    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
        {
            data->list[x][y].x = x;
            data->list[x][y].y = y;
            get_neighbourdata(data, x, y);
        }
    }
}
