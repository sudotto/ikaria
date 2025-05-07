#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "world.h"
#include "player.h"

int main(int argc, char* argv[]){
	srand(time(0));
	Game game = new_game("Arboria", 900, 600);
	int offset = 0;
	World world = new_world(&game, "AHHHHHH");
	Player player = new_player(&game, "player", 10);
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
		control_player(&game, &player);
		camera.x = (player.x + player.w) - (900 / 2);
		camera.y = (player.y + player.h) - (600 / 2);
		render_world(&game, &world);
		render_player(&game, &player);
		
		render_game_cursor(&game, 32, 32);
		update_game(&game);
		cap_game_framerate(&game, 60);
	}
	destroy_game(&game);
}
