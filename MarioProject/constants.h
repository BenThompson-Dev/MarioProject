#pragma once
//Screen Dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

//Level 1 Map Width and Height
#define LEVEL1_MAP_WIDTH 16
#define LEVEL1_MAP_HEIGHT 13
//Level 2 Map
#define LEVEL2_MAP_WIDTH 18
#define LEVEL2_MAP_HEIGHT 15

//Tile Size
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

//Amount of pixels moved over a second
#define MOVEMENT_SPEED 75.0f
#define INITIAL_JUMP_FORCE 600.0f

//Amount jumping force is reduced by over a second
#define JUMP_FORCE_DECREMENT 400.0f
#define GRAVITY 260.0f

//Height of character sprite
#define CHARACTER_SIZE 64

//Character collision radius
#define CHAR_COLLISION_RADIUS 15.0f

//Duration of POW Block screen shake
#define SHAKE_DURATION 0.25f

//Koopa injured time
#define INJURED_TIME 2.5f
//Koopa jump force
#define INITIAL_JUMP_FORCE_SMALL 200.0f
//Koopa speed
#define KOOPA_SPEED 96.0f
//Koopa respawn time
#define ENEMY_RESPAWN_TIME 7.5f
//Koopa score value
#define SCORE_INCREASE_KOOPA 15

//Coin respawn delay
#define COIN_RESPAWN_DELAY 3.0f
//Coin respawn time
#define COIN_RESPAWN_TIME 7.5f
//Coin speed
#define COIN_SPEED 120.0f
//Coin score value
#define SCORE_INCREASE_COIN 5

//Animation delay
#define ANIMATION_DELAY 0.25f

//Font sprite size
#define FONT_WIDTH 16
#define FONT_HEIGHT 16

//Max amount of digits on score display
#define SCORE_CHAR_AMOUNT 3