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

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <SDL2/SDL.h>

# include "../libft/libft.h"

# define    W_WIDTH     800
# define    W_HEIGHT    600

# define    NBTHREAD    6
# define    WTHREAD     W_WIDTH / NBTHREAD
# define    HTHREAD     W_HEIGHT / NBTHREAD

typedef struct  s_point
{
    int         i;
    int         x;
    int         y;
}               t_point;

typedef struct  s_node
{
    int             bobstacle;
    int             bvisited;
    int             i;
    int             x;
    int             y;
    float           globalgoal;
    float           localgoal;
    t_point         ngbhr[4];
    struct s_node   *parent;
}               t_node;

typedef struct  s_lst
{
    t_node          *node;
    struct s_lst    *next;
}               t_lst;

typedef struct  s_pf
{
    int             mw;
    int             mh;
    int             mlen;
    int             nborder;
    int             nsizex;
    int             nsizey;
    int             ctoken;
    int             stoken;
    int             sdl_on;
    t_point         mouse;
    t_point         snode;
    t_node          *start;
    t_node          *end;
    t_node          *list;
    t_lst           *alst;
    SDL_Event       event;
    SDL_Renderer    *renderer;
    SDL_Window	    *pWindow;
}               t_pf;

void            clean_exit(t_pf *data, char *str, int token);
void            display(t_pf *data);
void            event(t_pf *data);
void            get_list(t_pf *data);
void            get_nodes(t_pf *data);
void            solve_astar(t_pf *data);

void            lst_free(t_lst *list);
int             lst_len(t_lst *list);
void            lst_pushback(t_lst *list, t_node *node);
void            lst_sort(t_lst *list);

#endif
