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

static float    distance(t_node a, t_node b)
{
    return (ft_sqrt((a.x - b.x) * (a.x - b.x)
        + (a.y - b.y) * (a.y - b.y)));
}

static void     resetdata(t_pf *data)
{
    int i;

    i = -1;
    while (++i < data->mlen)
    {
        data->list[i].bvisited = 0;
        data->list[i].globalgoal = 2147483647;
        data->list[i].localgoal = 2147483647;
        data->list[i].parent = NULL;
    }
}

static void     neighbour(t_pf *data, t_node *current, int i)
{
    float   plowergoal;
    t_node  *ngbhr;

    ngbhr = &data->list[current->ngbhr[i].i];
    if (ngbhr->bvisited == 0 && ngbhr->bobstacle == 0)
        lst_pushback(data->alst, ngbhr);
    plowergoal = current->localgoal + distance(*current, *ngbhr);
    if (plowergoal < ngbhr->localgoal)
    {
        ngbhr->parent = current;
        ngbhr->localgoal = plowergoal;
        ngbhr->globalgoal = ngbhr->localgoal + distance(*ngbhr, *data->end);
    }
}

static void     delvisited_nodes(t_pf *data)
{    
    t_lst   *tmp;
    t_lst   *head;

    if (data->alst == NULL)
        return ;
    head = data->alst;
    while (data->alst && data->alst->node->bvisited == 1)
    {
        tmp = data->alst->next;
        ft_memdel((void **)&data->alst);
        data->alst = tmp;
        head = data->alst;
    }
    while (data->alst)
    {
        tmp = data->alst;
        data->alst = data->alst->next;
        while (data->alst && data->alst->node->bvisited == 1)
        {
            tmp->next = data->alst->next;
            ft_memdel((void **)&data->alst);
            data->alst = tmp->next;
        }
    }
    data->alst = head;
}

void            solve_astar(t_pf *data)
{
    t_node  *current;

    resetdata(data);
    current = data->start;
    current->localgoal = 0;
    current->globalgoal = distance(*data->start, *data->end);
    if (!(data->alst = (t_lst *)ft_memalloc(sizeof(t_lst))))
        clean_exit(data, "malloc error: astar.c", 0);
    data->alst->node = data->start;
    while (current != data->end)
    {
        lst_sort(data->alst);
        delvisited_nodes(data);
        if (!lst_len(data->alst))
            break ;
        current = data->alst->node;
        current->bvisited = 1;
        neighbour(data, current, 0);
        neighbour(data, current, 1);
        neighbour(data, current, 2);
        neighbour(data, current, 3);
    }
}
