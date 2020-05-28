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

static void     more_ngbhr(t_pf *data, int x, int y)
{
    t_node  **nodes;

    nodes = data->list;
    if (y > 0 && x > 0)
        nodes[x][y].ngbhr[4] = &nodes[x - 1][y - 1];
    if (x < data->mw - 1 && y < data->mh - 1)
        nodes[x][y].ngbhr[5] = &nodes[x + 1][y + 1];
    if (NEIGHBOURG > 6)
    {
        if (x < data->mw - 1 && y > 0)
            nodes[x][y].ngbhr[6] = &nodes[x + 1][y - 1];
        if (x > 0 && y < data->mh - 1)
            nodes[x][y].ngbhr[7] = &nodes[x - 1][y + 1];
    }
}

static void     get_neighbourdata(t_pf *data, int x, int y)
{
    int     i;
    t_node  **nodes;

    nodes = data->list;
    i = -1;
    while (++i < NEIGHBOURG)
        nodes[x][y].ngbhr[i] = NULL;
    if (y > 0)
        nodes[x][y].ngbhr[0] = &nodes[x][y - 1];
    if (y < data->mh - 1)
        nodes[x][y].ngbhr[1] = &nodes[x][y + 1];
    if (x > 0)
        nodes[x][y].ngbhr[2] = &nodes[x - 1][y];
    if (x < data->mw - 1)
        nodes[x][y].ngbhr[3] = &nodes[x + 1][y];
    if (NEIGHBOURG > 4)
        more_ngbhr(data, x, y);
}

static int      init_nodes(t_pf *data)
{
    int i;

    if (!(data->list = (t_node **)ft_memalloc(sizeof(t_node *) * (data->mw))))
        return (-1);
    i = -1;
    while (++i < data->mw)
    {
        if (!(data->list[i] = ft_memalloc(sizeof(t_node) * data->mh)))
            return (-1);
    }
    return (0);
}

void            get_nodes(t_pf *data)
{
    int     x;
    int     y;

    if (init_nodes(data))
        clean_exit(data, "error init_nodes", 0);
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
