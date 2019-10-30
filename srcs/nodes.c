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

static void     get_neighbourpos(t_pf *data)
{
    int i;

    i = -1;
    while (++i < data->mlen)
    {
        data->list[i].ngbhr[0].x = data->list[data->list[i].ngbhr[0].i].x;
        data->list[i].ngbhr[0].y = data->list[data->list[i].ngbhr[0].i].y;
        data->list[i].ngbhr[1].x = data->list[data->list[i].ngbhr[1].i].x;
        data->list[i].ngbhr[1].y = data->list[data->list[i].ngbhr[1].i].y;
        data->list[i].ngbhr[2].x = data->list[data->list[i].ngbhr[2].i].x;
        data->list[i].ngbhr[2].y = data->list[data->list[i].ngbhr[2].i].y;
        data->list[i].ngbhr[3].x = data->list[data->list[i].ngbhr[3].i].x;
        data->list[i].ngbhr[3].y = data->list[data->list[i].ngbhr[3].i].y;
    }
}

static void     get_neighbourdata(t_pf *data)
{
    int     x;
    int     y;

    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
        {
            if (y > 0)
                data->list[x + y * data->mw].ngbhr[0].i
                    = data->list[(y - 1) * data->mw + (x + 0)].i;
            if (y < data->mh - 1)
                data->list[x + y * data->mw].ngbhr[1].i
                    = data->list[(y + 1) * data->mw + (x + 0)].i;
            if (x > 0)
                data->list[x + y * data->mw].ngbhr[2].i
                    = data->list[(y + 0) * data->mw + (x - 1)].i;
            if (x < data->mw - 1)
                data->list[x + y * data->mw].ngbhr[3].i
                    = data->list[(y + 0) * data->mw + (x + 1)].i;
        }
    }
    get_neighbourpos(data);
}

void            get_nodes(t_pf *data)
{
    int     i;
    int     x;
    int     y;

    if (!(data->list = (t_node *)ft_memalloc(sizeof(t_node)
    * (data->mh * data->mw))))
        clean_exit(data, "malloc error", 0);
    i = 0;
    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
        {
            data->list[i].i = i;
            ++i;
            data->list[y * data->mw + x].x = x;
            data->list[y * data->mw + x].y = y;
        }
    }
    get_neighbourdata(data);
}
