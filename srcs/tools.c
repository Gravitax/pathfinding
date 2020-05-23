/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:08:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pathfinding.h"

void            clean_exit(t_pf *data, char *str, int token)
{
    if (data)
    {
        ft_memdel((void **)&data->list);
        free_dynarray(&data->d_astar);
        if (data->sdl_on)
        {
            if (data->pWindow)
                SDL_DestroyWindow(data->pWindow);
            if (data->renderer)
                SDL_DestroyRenderer(data->renderer);
            SDL_Quit();
        }
    }
    if (str)
       ft_putendl_fd(str, 2);
    exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}
