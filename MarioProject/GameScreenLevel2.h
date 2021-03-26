#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "LevelMap.h"

class Texture2D;
class AudioManager;

class GameScreenLevel2 : GameScreen
{
private:
	Texture2D* m_background_texture;
	Character* mario;

	LevelMap* m_level_map;
	AudioManager* m_audio_manager;

	bool SetUpLevel();
	void SetLevelMap();
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render(float deltaTime) override;
	void Update(float deltaTime, SDL_Event e) override;
};

#endif //_GAMESCREENLEVEL2_H