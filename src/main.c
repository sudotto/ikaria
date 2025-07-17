#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

int main(int argc, char* argv[]){
	srand(time(0));
	Game game = new_game("");
	while(game.running){
		game.frame_start = SDL_GetTicks();
		clear_game(&game, 0, 0, 255);

		while(get_game_events(&game)){
			switch(game.event.type){
				case SDL_EVENT_QUIT:
					game.running = false;
					break;
			}
		}



		render_game_cursor(&game, 64, 64);
		update_game(&game);
		cap_game_framerate(&game, 60);
	}
	destroy_game(&game);
}
