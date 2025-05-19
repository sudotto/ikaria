#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "world.h"

#include "player.h"

Player new_player(Game* game, char* name, float walk_spd){
	Player player;
	player.x = (WORLD_SIZE * (16 * 4)) / 2;
	player.y = (WORLD_SIZE * (16 * 4)) / 2;
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
		"/walk.png"
	};
	for(int anim = 0; anim < ANIM_COUNT; anim++){
		for(int facing = 0; facing < 4; facing++){
			strcpy(filepath, dirname);
			strcat(filepath, filenames[anim]);
			player.anims[anim][facing] = new_anim(game->rend, filepath, 4, facing, 16 * 10, 16 * 10, true);
		}
	}
	player.anim = IDLE;
	free(dirname);
	free(filepath);
	return player;
}

void control_player(Game* game, Player* player, World* world){
	if(game->keystates[SDL_SCANCODE_W]){
		player->facing = UP;
		player->y_vel = -player->walk_spd;
	}
	if(game->keystates[SDL_SCANCODE_A]){
		player->facing = LEFT;
		player->x_vel = -player->walk_spd;
	}
	if(game->keystates[SDL_SCANCODE_S]){
		player->facing = DOWN;
		player->y_vel = player->walk_spd;
	}
	if(game->keystates[SDL_SCANCODE_D]){
		player->facing = RIGHT;
		player->x_vel = player->walk_spd;
	}
	int standing_x = (int)((player->x + player->w / 2) / (16 * 4)); 
	int standing_y = (int)((player->y + player->h / 2) / (16 * 4)); 
	Tile tile = world->tiles[standing_y][standing_x];
	if(tile.type == TILE_WATER){
		player->facing = UP;
	} else {
		player->facing = DOWN;
	}
	update_player(game, player, world);
}

void update_player(Game* game, Player* player, World* world){
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

	if(player->x_vel != 0 || player->y_vel != 0){
		player->anim = WALK;
	} else {
		player->anim = IDLE;
	}
}

void render_player(Game* game, Player* player){
	render_anim(game->rend, &player->anims[player->anim][player->facing], player->x, player->y, player->w, player->h, 0.1);
}
