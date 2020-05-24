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
        {
            data->ctoken = data->ctoken ? 0 : 1;
            if (data->ctoken && data->stoken)
                data->stoken = 0;
        }
        if (data->event.key.keysym.sym == SDLK_LSHIFT)
        {
            data->stoken = data->stoken ? 0 : 1;
            if (data->stoken && data->ctoken)
                data->ctoken = 0;
        }
    }
}

static void     mouse_event(t_pf *data)
{
    if (data->event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (data->snode.x >= 0 && data->snode.x < data->mw
        && data->snode.y >= 0 && data->snode.y < data->mh)
        {
            if (data->ctoken)
            {
                data->end = &data->list[data->snode.x][data->snode.y];
            }
            else if (data->stoken)
            {
                data->start = &data->list[data->snode.x][data->snode.y];
            }
            else
            {
                data->list[data->snode.x][data->snode.y].bobstacle
                    = !data->list[data->snode.x][data->snode.y].bobstacle;
            }
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
