#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

#include "otto-game.h"

#define ANIM_COUNT 2

typedef enum {
	UP,
	DOWN,
	RIGHT,
	LEFT,
} Facing;

typedef enum {
	IDLE,
	WALK,
} Curr_anim;

typedef struct {
	char* name;
	Anim anims[ANIM_COUNT][4];
	Curr_anim anim;
	Facing facing;
	float x;
	float y;
	int w;
	int h;
	float x_vel;
	float y_vel;
	int walk_spd;
} Player;

Player new_player(Game* game, char* name, float walk_spd);
void control_player(Game* game, Player* player);
void move_player(Player* player);
void render_player(Game* game, Player* player);

#endif
