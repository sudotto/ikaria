#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "player.h"

Player new_player(SDL_Renderer* rend, char* name, float walk_spd){
	Player player;
	player.x = 10;
	player.y = 10;
	player.w = 64;
	player.h = 64;
	player.x_vel = 0;
	player.y_vel = 0;
	player.walk_spd = 5;

	player.facing = DOWN;

	char* dirname = malloc(sizeof(char) * 20);
	strcpy(dirname, "assets/");
	strcat(dirname, name);

	char* filepath = malloc(sizeof(char) * 30);

	char* filenames[ANIM_COUNT] = {
		"/idle.png",
		"/idle.png"
	};

	for(int anim = 0; anim < ANIM_COUNT; anim++){
		for(int facing = 0; facing < 4; facing++){
			strcpy(filepath, dirname);
			strcat(filepath, filenames[anim]);
			player.anims[anim][facing] = new_anim(rend, filepath, 4, facing, 32 * 10, 32 * 10);
		}
	}

	player.anim = IDLE;

	free(dirname);
	free(filepath);
	return player;
}

void control_player(Player* player, const bool* keystates){
	player->anim = IDLE;
	if(keystates[SDL_SCANCODE_W]){
		player->facing = UP;
		player->y_vel = -player->walk_spd;
	}
	if(keystates[SDL_SCANCODE_A]){
		player->facing = LEFT;
		player->x_vel = -player->walk_spd;
	}
	if(keystates[SDL_SCANCODE_S]){
		player->facing = DOWN;
		player->y_vel = player->walk_spd;
	}
	if(keystates[SDL_SCANCODE_D]){
		player->facing = RIGHT;
		player->x_vel = player->walk_spd;
	}
	move_player(player);
}

void move_player(Player* player){
	printf("%f\n",player->x_vel);
	int friction = 1;

	player->y += player->y_vel;
	if(player->y_vel < 0){
		player->y_vel += 1;
	} else if(player->y_vel > 0){
		player->y_vel -= 1;
	} else {
		player->y_vel = 0;
	}

	player->x += player->x_vel;
	if(player->x_vel < 0){
		player->x_vel += 1;
	} else if(player->x_vel > 0){
		player->x_vel -= 1;
	} else {
		player->x_vel = 0;
	}
}

void render_player(SDL_Renderer* rend, Player* player){
	render_anim(rend, &player->anims[player->anim][player->facing], player->x, player->y, player->w, player->h, 0.1);
}
