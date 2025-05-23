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
	player.walk_spd = 2;
	player.swim_spd = 1;
	player.facing = DOWN;
	char* dirname = malloc(sizeof(char) * 20);
	strcpy(dirname, "assets/");
	strcat(dirname, name);
	char* filepath = malloc(sizeof(char) * 30);
	char* filenames[ANIM_COUNT] = {
		"/idle.png",
		"/walk.png",
		"/swim.png"
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
	int spd = 0;
	Tile tile = world->tiles[(int)((player->y + player->h / 2) / (16 * 4))][(int)((player->x + player->w / 2) / (16 * 4))];
	if(tile.type == TILE_WATER){
		player->anim = SWIM;
	} else {
		player->anim = IDLE;
	}

	if(game->keystates[SDL_SCANCODE_W]){
		player->facing = UP;
		if(tile.type == TILE_WATER){
			player->anim = SWIM;
			player->y_vel = -player->swim_spd;
		} else {
			player->anim = WALK;
			player->y_vel = -player->walk_spd;
		}
	}
	if(game->keystates[SDL_SCANCODE_A]){
		player->facing = LEFT;
		player->x_vel = -spd;
		if(tile.type == TILE_WATER){
			player->anim = SWIM;
			player->x_vel = -player->swim_spd;
		} else {
			player->anim = WALK;
			player->x_vel = -player->walk_spd;
		}
	}
	if(game->keystates[SDL_SCANCODE_S]){
		player->facing = DOWN;
		player->y_vel = spd;
		if(tile.type == TILE_WATER){
			player->anim = SWIM;
			player->y_vel = player->swim_spd;
		} else {
			player->anim = WALK;
			player->y_vel = player->walk_spd;
		}
	}
	if(game->keystates[SDL_SCANCODE_D]){
		player->facing = RIGHT;
		if(tile.type == TILE_WATER){
			player->anim = SWIM;
			player->x_vel = player->swim_spd;
		} else {
			player->anim = WALK;
			player->x_vel = player->walk_spd;
		}
	}
	update_player(game, player, world);
}

void update_player(Game* game, Player* player, World* world){
	player->y += player->y_vel * 4;
	if(player->y_vel < 0){
		player->y_vel += 1;
	} else if(player->y_vel > 0){
		player->y_vel -= 1;
	} else {
		player->y_vel = 0;
	}

	player->x += player->x_vel * 4;
	if(player->x_vel < 0){
		player->x_vel += 1;
	} else if(player->x_vel > 0){
		player->x_vel -= 1;
	} else {
		player->x_vel = 0;
	}
}

void render_player(Game* game, Player* player){
	render_anim(game->rend, &player->anims[player->anim][player->facing], player->x, player->y, player->w, player->h, 0.1);
}
