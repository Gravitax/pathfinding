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

static void     connection(t_pf *data, int i)
{
    if (data->list[i].ngbhr[0].i > 0)
        SDL_RenderDrawLine(data->renderer,
            data->list[i].x * data->nsizex + data->nsizex / 2,
            data->list[i].y * data->nsizey + data->nsizey / 2,
            data->list[i].ngbhr[0].x * data->nsizex + data->nsizex / 2,
            data->list[i].ngbhr[0].y * data->nsizey + data->nsizey / 2);
    if (data->list[i].ngbhr[1].i > 0)
        SDL_RenderDrawLine(data->renderer,
            data->list[i].x * data->nsizex + data->nsizex / 2,
            data->list[i].y * data->nsizey + data->nsizey / 2,
            data->list[i].ngbhr[1].x * data->nsizex + data->nsizex / 2,
            data->list[i].ngbhr[1].y * data->nsizey + data->nsizey / 2);
    if (data->list[i].ngbhr[2].i > 0)
        SDL_RenderDrawLine(data->renderer,
            data->list[i].x * data->nsizex + data->nsizex / 2,
            data->list[i].y * data->nsizey + data->nsizey / 2,
            data->list[i].ngbhr[2].x * data->nsizex + data->nsizex / 2,
            data->list[i].ngbhr[2].y * data->nsizey + data->nsizey / 2);
    if (data->list[i].ngbhr[3].i > 0)
        SDL_RenderDrawLine(data->renderer,
            data->list[i].x * data->nsizex + data->nsizex / 2,
            data->list[i].y * data->nsizey + data->nsizey / 2,
            data->list[i].ngbhr[3].x * data->nsizex + data->nsizex / 2,
            data->list[i].ngbhr[3].y * data->nsizey + data->nsizey / 2);
}

static void     blocks(t_pf *data)
{
    int         i;
    SDL_Rect    rect;

    i = -1;
    while (++i < data->mlen)
    {
        SDL_SetRenderDrawColor(data->renderer, 150, 50, 50, 100);
        rect.w = data->nsizex - data->nborder;
        rect.h = data->nsizey - data->nborder;
        rect.x = data->list[i].x * data->nsizex + data->nborder / 2;
        rect.y = data->list[i].y * data->nsizey + data->nborder / 2;
        if (data->list[i].bobstacle == 1)
            SDL_SetRenderDrawColor(data->renderer, 85, 06, 06, 100);
        if (data->list[i].bvisited == 1)
            SDL_SetRenderDrawColor(data->renderer, 15, 05, 107, 100);
        if (data->list[i].i == data->start->i)
            SDL_SetRenderDrawColor(data->renderer, 0, 0, 255, 100);
        if (data->list[i].i == data->end->i)
            SDL_SetRenderDrawColor(data->renderer, 100, 10, 150, 100);
        SDL_RenderFillRect(data->renderer, &rect);
    }
}

void            display(t_pf *data)
{
    data->nborder = 8;
    data->nsizex = W_WIDTH / data->mw;
    data->nsizey = W_HEIGHT / data->mh;
    data->snode.x = data->mouse.x / data->nsizex;
    data->snode.y = data->mouse.y / data->nsizey;

    SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
    for (int x = 0; x < data->mw; x++)
        for (int y = 0; y < data->mh; y++)
            connection(data, x + y * data->mw);
    blocks(data);
    if (data->end != NULL)
    {
        SDL_SetRenderDrawColor(data->renderer, 255, 100, 100, 100);
        t_node  *tmp = data->end;
        while (tmp->parent != NULL)
        {
            SDL_RenderDrawLine(data->renderer,
                tmp->x * data->nsizex + data->nsizex / 2,
                tmp->y * data->nsizey + data->nsizey / 2,
                tmp->parent->x * data->nsizex + data->nsizex / 2,
                tmp->parent->y * data->nsizey + data->nsizey / 2);
          tmp = tmp->parent;
        }
    }
    SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
}
