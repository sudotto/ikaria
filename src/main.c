#include <stdio.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "player.h"

int main(int argc, char* argv[]){
	Game game = new_game("Arboria", 900, 600);
	int offset = 0;
	Img grass = new_img(game.rend, "assets/tiles/stone.png");
	Player player = new_player(game.rend, "player", 10);
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
		control_player(&player, game.keystates);
		for(int y = -1; y < 61; y++){
			for(int x = -1; x < 91; x++){
				render_img(game.rend, &grass, (x * 64) + offset, (y * 64) + offset, 64, 64);
			}
		}
		render_player(game.rend, &player);
		
		render_game_cursor(&game, 32, 32);
		update_game(&game);
		cap_game_framerate(60, game.frame_start);
	}
	destroy_game(&game);
}
