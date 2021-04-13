#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "GameScreen.h"
#include "Commons.h"
#include <vector>

class Texture2D;
class AudioManager;
class Character;
class CharacterMario;
class CharacterCoin;
class LevelMapLevel2;

class GameScreenLevel2 : public GameScreen
{
private:
	Texture2D* m_background_texture;

	Character* mario;
	CharacterCoin* coin;
	LevelMapLevel2* m_level_map;

	AudioManager* m_audio_manager;

	std::vector<CharacterCoin*> m_coins;

	bool SetUpLevel();
	void SetLevelMap();

	void UpdateEnemies(float deltaTime, SDL_Event e);

	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position, FACING direction, float speed);
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render(float deltaTime) override;
	void Update(float deltaTime, SDL_Event e) override;
};

#endif //_GAMESCREENLEVEL2_H