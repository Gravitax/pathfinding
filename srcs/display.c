/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

static void     connection(t_pf *data, int x, int y)
{
    for (int k = 0; k < 4; k++)
    {
        if (data->list[x][y].ngbhr[k])
            SDL_RenderDrawLine(data->renderer,
                data->list[x][y].x * data->nsizex + data->nsizex / 2,
                data->list[x][y].y * data->nsizey + data->nsizey / 2,
                data->list[x][y].ngbhr[k]->x * data->nsizex + data->nsizex / 2,
                data->list[x][y].ngbhr[k]->y * data->nsizey + data->nsizey / 2);
    }
}

static void     get_color(t_pf *data, int x, int y)
{
    if (data->list[x][y].bobstacle == 1)
        SDL_SetRenderDrawColor(data->renderer, 85, 06, 06, 100);
    if (data->list[x][y].bvisited == 1)
        SDL_SetRenderDrawColor(data->renderer, 15, 05, 107, 100);
    if (&data->list[x][y] == data->start)
        SDL_SetRenderDrawColor(data->renderer, 0, 0, 255, 100);
    if (&data->list[x][y] == data->end)
        SDL_SetRenderDrawColor(data->renderer, 100, 10, 150, 100);
}

static void     blocks(t_pf *data)
{
    int         x;
    int         y;
    SDL_Rect    rect;

    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
        {
            SDL_SetRenderDrawColor(data->renderer, 150, 50, 50, 100);
            rect.w = data->nsizex - data->nborder;
            rect.h = data->nsizey - data->nborder;
            rect.x = data->list[x][y].x * data->nsizex + data->nborder / 2;
            rect.y = data->list[x][y].y * data->nsizey + data->nborder / 2;
            get_color(data, x, y);
            SDL_RenderFillRect(data->renderer, &rect);
        }
    }
}

static void     parents(t_pf *data)
{
    int     x;
    int     y;
    t_node  *tmp;

    x = 0;
    y = 0;
    if (data->end != NULL)
    {
        SDL_SetRenderDrawColor(data->renderer, 255, 100, 100, 100);
        tmp = data->end;
        while (tmp && tmp != data->start)
        {
            if (tmp->parent)
            {
                SDL_RenderDrawLine(data->renderer,
                    tmp->x * data->nsizex + data->nsizex / 2,
                    tmp->y * data->nsizey + data->nsizey / 2,
                    tmp->parent->x * data->nsizex + data->nsizex / 2,
                    tmp->parent->y * data->nsizey + data->nsizey / 2);
            }
            x = tmp->x;
            y = tmp->y;
            tmp = tmp->parent;
        }
        //SDL_Delay(100);
        if (data->start == data->end)
        {
            printf("total time: %f\n", (double)((clock() - data->time) / CLOCKS_PER_SEC));
            exit(0);
        }
        data->start = &data->list[x][y];
    }
}

void            display(t_pf *data)
{
    int x;
    int y;

    data->nborder = 8;
    data->nsizex = W_WIDTH / data->mw;
    data->nsizey = W_HEIGHT / data->mh;
    data->snode.x = data->mouse.x / data->nsizex;
    data->snode.y = data->mouse.y / data->nsizey;
    SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
    x = -1;
    while (++x < data->mw)
    {
        y = -1;
        while (++y < data->mh)
            connection(data, x, y);
    }
    blocks(data);
    parents(data);
    SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
}
