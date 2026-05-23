#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include "game/State.h"

class GameEngine;

class ImGuiDebug
{
private:
	GameEngine* gameEngine;
public:
	ImGuiDebug(GameEngine* gameEngine);

	void show(sf::Time dt);

	void pauseButton();

	void pipeGap();

	void birdGravity();
};