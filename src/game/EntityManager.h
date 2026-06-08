#pragma once

#include "GameObject.h"
#include "Bird.h"
#include "Pipe.h"
#include "Obstacle.h"

class GameEngine;

class EntityManager
{
private:
	GameEngine* gameEngine;
	Bird bird;
	Obstacle obstacle1{ true  };
	Obstacle obstacle2{ false };
	sf::RectangleShape background;
public:
	float pipeGap = 100.f;
	float &jumpForce;
	float &gravityForce;

	EntityManager(GameEngine* gameEngine);

	void drawAll(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event);
	void updateAll(float dt);
	Bird& getBird();
	void updatePipeGap();
	Obstacle& getCloserObstacle();
	void reset();
};