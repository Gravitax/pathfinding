/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

static void     init_sdl(t_pf *data)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
        clean_exit(data, "sdl init error", 0);
    data->sdl_on = 1;
    data->pWindow = SDL_CreateWindow("maboye pathfinding",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGHT, 0);
}

static void     pathfinding(t_pf *data)
{
    init_sdl(data);
    if (data->pWindow)
    {
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "sdl renderer error", 0);
        data->mw = 32;
        data->mh = 32;
        data->mlen = data->mw * data->mh;
        get_nodes(data);
        data->start = &data->list[0];
        data->end = &data->list[data->mw * data->mh - 1];
        for (;;)
        {
            SDL_RenderClear(data->renderer);
            event(data);
            solve_astar(data);
            display(data);
            SDL_RenderPresent(data->renderer);
        }
    }
    clean_exit(data, NULL, 1);
}

int             main(int ac, char **av)
{
    t_pf    data;

    if (ac == 1 && av[1] == NULL)
    {
        ft_memset(&data, 0, sizeof(t_pf));
        pathfinding(&data);
    }
    return (0);
}
