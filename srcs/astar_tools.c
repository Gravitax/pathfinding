/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

int             place_pivot(t_dynarray *array, int low, int high)
{
	int     pivot;
	int     switch_i;
	int     i;

    pivot = low;
    i = low + 1;
    switch_i = low + 1;
	while (i <= high)
	{
		if (((t_node *)dyacc(array, i))->globalgoal
            < ((t_node *)dyacc(array, pivot))->globalgoal)
		{
            dynnaray_swap_cells(array, i, switch_i);
            dynnaray_swap_cells(array, pivot, switch_i);
			++pivot;
			++switch_i;
		}
        ++i;
	}
	return (pivot);
}

void            quicksort(t_dynarray *array, int low, int high)
{
    int     pivot;

	if (low >= high)
		return;
	pivot = place_pivot(array, low, high); 
	quicksort(array, low, pivot - 1);
	quicksort(array, pivot + 1, high);
}

void            bubble_sort(t_dynarray *arr)
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

void            sort_dynarray(t_dynarray *arr)
{
    //bubble_sort(arr);
    quicksort(arr, 0, arr->nb_cells - 1);
}

void            delvisited_nodes(t_dynarray *arr)
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

float           distance(t_node a, t_node b)
{
    return (ft_sqrt((a.x - b.x) * (a.x - b.x)
        + (a.y - b.y) * (a.y - b.y)));
}

void            resetdata(t_pf *data)
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
