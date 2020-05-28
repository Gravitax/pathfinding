/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

static void     key_event(t_pf *data)
{
    if (data->event.type == SDL_KEYUP)
    {
        if (data->event.key.keysym.sym == SDLK_LCTRL)
            data->ctoken = data->ctoken ? 0 : 1;
        else if (data->event.key.keysym.sym == SDLK_LSHIFT)
            data->stoken = data->stoken ? 0 : 1;
        if (data->stoken && data->ctoken)
            data->ctoken = 0;
    }
}

static void     mouse_event(t_pf *data)
{
    t_point p;

    p = data->snode;
    if (data->event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (p.x >= 0 && p.x < data->mw
            && p.y >= 0 && p.y < data->mh)
        {
            if (data->ctoken)
                data->end = &data->list[p.x][p.y];
            else if (data->stoken)
                data->start = &data->list[p.x][p.y];
            else
                data->list[p.x][p.y].bobstacle = !data->list[p.x][p.y].bobstacle;
        }
    }
}

void            event(t_pf *data)
{
    while (SDL_PollEvent(&data->event))
    {
        if (data->event.type == SDL_QUIT)
            clean_exit(data, NULL, 1);
        if (data->event.key.keysym.sym == SDLK_ESCAPE)
            clean_exit(data, NULL, 1);
        if (data->event.type == SDL_MOUSEMOTION)
        {
            data->mouse.x = data->event.motion.x;
            data->mouse.y = data->event.motion.y;
        }
        key_event(data);
        mouse_event(data);
    }
}
