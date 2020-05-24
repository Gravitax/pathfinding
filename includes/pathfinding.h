/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:10:56 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDING_H
# define PATHFINDING_H

# include <SDL2/SDL.h>

# include "dynarray.h"
# include "../libft/libft.h"

# define    W_WIDTH     800
# define    W_HEIGHT    600

typedef struct  s_point
{
    int         x;
    int         y;
}               t_point;

typedef struct  s_node
{
    int             bobstacle;
    int             bvisited;
    int             x;
    int             y;
    float           globalgoal;
    float           localgoal;
    struct s_node   *ngbhr[4];
    struct s_node   *parent;
}               t_node;

typedef struct  s_pf
{
    int             mw;
    int             mh;
    int             nborder;
    int             nsizex;
    int             nsizey;
    int             ctoken;
    int             stoken;
    int             sdl_on;
    t_dynarray      d_astar;
    t_point         mouse;
    t_point         snode;
    t_node          *start;
    t_node          *end;
    t_node          **list;
    SDL_Event       event;
    SDL_Renderer    *renderer;
    SDL_Window	    *pWindow;
}               t_pf;

void            clean_exit(t_pf *data, char *str, int token);
void            display(t_pf *data);
void            event(t_pf *data);

void            get_nodes(t_pf *data);
void            astar(t_pf *data);

#endif
