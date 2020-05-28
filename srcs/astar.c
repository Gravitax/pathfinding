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

void            quick_sort(t_dynarray *data, int left, int right)
{
    int     left_index;
    int     right_index;
    float   pivot;

    left_index = left;
    right_index = right;
    pivot = ((t_node *)dyacc(data, (left + right) / 2))->globalgoal;
    while (left_index <= right_index)
    {
        while (((t_node *)dyacc(data, left_index))->globalgoal < pivot)
            ++left_index;
        while (((t_node *)dyacc(data, right_index))->globalgoal > pivot)
            --right_index;
        if (left_index <= right_index)
        {
            dynnaray_swap_cells(data, left_index, right_index);
            ++left_index;
            --right_index;
        }
    }
    if (right_index > left)
        quick_sort(data, left, right_index);
    if (left_index < right)
        quick_sort(data, left_index, right);
}

void            astar_sort_dynarray(t_dynarray *arr)
{
    quick_sort(arr, 0, arr->nb_cells - 1);
}
/*
void     bubble_sort(t_dynarray *arr)
{
	int	    i;
	int	    j;
    t_node  *d1;
    t_node  *d2;

	i = -1;
	while (++i < arr->nb_cells - 1)
	{
		j = -1;
		while (++j < arr->nb_cells - 1)
		{
            d1 = dyacc(arr, j);
            d2 = dyacc(arr, j + 1);
			if (d1->globalgoal > d2->globalgoal)
                dynnaray_swap_cells(arr, j, j + 1);
		}
	}
}
*/
static void     sort_dynarray(t_dynarray *arr)
{
    //bubble_sort(arr);
    astar_sort_dynarray(arr);
}

static void     delvisited_nodes(t_dynarray *arr)
{
    int     i;
    t_node  *d;

    i = -1;
    while (++i < arr->nb_cells)
    {
        d = dyacc(arr, i);
        if (d->bvisited)
            extract_dynarray(arr, i);
    }
}

static float    distance(t_node a, t_node b)
{
    return (ft_sqrt((a.x - b.x) * (a.x - b.x)
        + (a.y - b.y) * (a.y - b.y)));
}

static void     resetdata(t_pf *data)
{
    int x;
    int y;

    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
        {
            data->list[x][y].bvisited = 0;
            data->list[x][y].globalgoal = INFINITY;
            data->list[x][y].localgoal = INFINITY;
            data->list[x][y].parent = NULL;
        }
    }
    clear_dynarray(&data->d_astar);
}

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

    resetdata(data);
    push_dynarray(&data->d_astar, data->start, 0);
    current = data->d_astar.c;
    current->localgoal = 0;
    current->globalgoal = distance(*data->start, *data->end);
    while (solve_astar(data, current) == 0)
        ;
}
