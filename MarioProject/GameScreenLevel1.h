#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

//File references
#include "GameScreen.h" //includes SDL.h as it is included in GameScreen.h
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "LevelMap.h";
#include <vector>

class Texture2D; //Forward declaration of class
class POWBlock;
class PlayerScore;

class GameScreenLevel1 : GameScreen // Inherits from class type GameScreen
{
	private:
		Texture2D* m_background_texture; //Reference to Texture2D, can be used because of forward declaration
		Texture2D* m_background_colour; //Creates background colour for the image
		Character* mario; //Character references
		Character* luigi;
		CharacterKoopa* koopa;
		CharacterCoin* coin;
		LevelMap* m_level_map;
		POWBlock* m_pow_block;

		PlayerScore* m_player_score;

		bool m_screenshake;
		float m_shake_time;
		float m_wobble;
		float m_background_yPos;

		float enemyRespawnCounter = 0;
		float coinRespawnCounter;

		std::vector<CharacterKoopa*> m_enemies;
		std::vector<CharacterCoin*> m_coins;

		bool SetUpLevel(); //private function only used by this class
		void SetLevelMap();
		void DoScreenShake();

		void UpdateEnemies(float deltaTime, SDL_Event e);
		void CreateKoopa(Vector2D position, FACING direction, float speed);

		void UpdateCoins(float deltaTime, SDL_Event e);
		void CreateCoin(Vector2D position, FACING direction, float speed);
	public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render(float deltaTime) override; //override is optional but good practice to understand the code better
		void Update(float deltaTime, SDL_Event e) override;
		void UpdatePOWBlock();
};

#endif //_GAMESCREENLEVEL1_H