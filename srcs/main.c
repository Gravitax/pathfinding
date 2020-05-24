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
        clean_exit(data, "SDL_Init error", 0);
    data->sdl_on = 1;
    data->pWindow = SDL_CreateWindow("maboye pathfinding",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGHT, 0);
}

static void     init_data(t_pf *data)
{
    if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
        clean_exit(data, "SDL_CreateRenderer error", 0);
    data->mw = 10;
    data->mh = 10;
    get_nodes(data);
    data->start = &data->list[0][0];
    data->end = &data->list[data->mw - 1][data->mh - 1];
    if (init_dynarray(&data->d_astar, sizeof(t_node), 1))
        clean_exit(data, "init_dynarray error", 0);
}

static void     pathfinding(t_pf *data)
{
    init_sdl(data);
    if (data->pWindow)
    {
        init_data(data);
        for (;;)
        {
            SDL_RenderClear(data->renderer);
            event(data);
            astar(data);
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
