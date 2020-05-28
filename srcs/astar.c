/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

static void     stock_neighbour(t_pf *data, t_node *ngbhr)
{
    int     i;
    t_node  *d;

    i = -1;
    while (++i < data->d_astar.nb_cells)
    {
        d = dyacc(&data->d_astar, i);
        if (d->x == ngbhr->x
            && d->y == ngbhr->y)
            return ;
    }
    push_dynarray(&data->d_astar, ngbhr, 0);
}

static void     neighbour(t_pf *data, t_node **current, int i)
{
    float   plowergoal;
    t_node  *ngbhr;

    ngbhr = (*current)->ngbhr[i];
    if (ngbhr == NULL)
        return ;
    if (ngbhr->bobstacle || ngbhr->bvisited)
        return ;
    plowergoal = (*current)->localgoal + distance(**current, *ngbhr);
    if (plowergoal < ngbhr->localgoal)
    {
        ngbhr->parent = &data->list[(*current)->x][(*current)->y];
        ngbhr->localgoal = plowergoal;
        ngbhr->globalgoal = ngbhr->localgoal + distance(*ngbhr, *data->end);
    }
    if (ngbhr->bvisited == 0 && ngbhr->bobstacle == 0)
        stock_neighbour(data, ngbhr);
    *current = data->d_astar.c;
}

static int      exit_astar(t_pf *data, t_node *current)
{
    return ((current->x == data->end->x
        && current->y == data->end->y)
        || data->d_astar.nb_cells < 1);
}

static int      solve_astar(t_pf *data, t_node *current)
{
    int i;

    sort_dynarray(&data->d_astar);
    delvisited_nodes(&data->d_astar);
    current = data->d_astar.c;
    current->bvisited = 1;
    data->list[current->x][current->y].bvisited = 1;
    if (exit_astar(data, current))
        return (1);
    i = -1;
    while (++i < NEIGHBOURG)
        neighbour(data, &current, i);
    return (0);
}

void            astar(t_pf *data)
{
    t_node  *current;
    clock_t t;

    t = clock();
    resetdata(data);
    push_dynarray(&data->d_astar, data->start, 0);
    current = data->d_astar.c;
    current->localgoal = 0;
    current->globalgoal = distance(*data->start, *data->end);
    while (solve_astar(data, current) == 0)
        ;
    t = clock() - t;
    printf("time: %f\n", (double)t / CLOCKS_PER_SEC);
}
