/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:08 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/07 18:19:26 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sdl_error(char *message)
{
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(-1);
}

void			init_sdl(t_rt *rt)
{
	rt->win = NULL;
	rt->rend = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 &&
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
		sdl_error("initialisation SDL");
	if (!(rt->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, MAXWIDTH, MAXHEIGHT, SDL_WINDOW_SHOWN)))
		sdl_error("Creation window");
	if (!(rt->rend = SDL_CreateRenderer(rt->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		sdl_error("Creation render");
}

void			loop(t_rt *rt)
{
	SDL_bool	prog_launched;
	SDL_Event	event;

	SDL_RenderPresent(rt->rend);
	prog_launched = SDL_TRUE;
	while (prog_launched)
	{
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						|| event.type == SDL_QUIT)
			{
				ft_free(&rt->obj, &rt->lights, &rt->cam);
				prog_launched = SDL_FALSE;
				exit(1);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			{
				rt->menu = 1;
				rt->filter_type = 0;
				SDL_RenderClear(rt->rend);
				draw(*rt);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
			{
				rt->menu = 0;
				SDL_RenderClear(rt->rend);
				draw(*rt);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&(rt->event.i), &(rt->event.j));
				SDL_RenderClear(rt->rend);
				draw(*rt);
			}
		}
	}
	SDL_DestroyRenderer(rt->rend);
	SDL_DestroyWindow(rt->win);
	SDL_Quit();
}