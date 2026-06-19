#pragma once

#include "GameObject.h"
#include "Bird.h"
#include "Pipe.h"
#include "Obstacle.h"
#include "Menu.h"
#include "Concepts.h"

class GameEngine;

class EntityManager
{
private:
	GameEngine* gameEngine;
	Bird bird;
	Obstacle obstacle1{ true  };
	Obstacle obstacle2{ false };
	sf::RectangleShape background;
	sf::Font scoreFont;
	sf::Text scoreText;
	Menu menu;
public:
	float pipeGap = 100.f;
	float &jumpForce;
	float &gravityForce;

	EntityManager(GameEngine* gameEngine);

	void drawAll(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event);
	void updateAll(float dt);

	template <Renderable T>
	void drawComponent(T& component, sf::RenderWindow& window);

	Bird& getBird();
	void updatePipeGap();
	Obstacle& getCloserObstacle();
	void reset();
	void pause();
	void gameOver();
	void resetScoreText();
};