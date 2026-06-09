#pragma once

#include "EntityManager.h"
#include "GameEngine.h"
#include "State.h"
#include <iostream>

EntityManager::EntityManager(GameEngine* gameEngine)
	: gravityForce(bird.gravityForce),
	  jumpForce(bird.jumpForce),
	  gameEngine(gameEngine),
	  scoreText(scoreFont)
{
	gameEngine->scoreManager.setText(&scoreText); //Must be set 

	if (!scoreFont.openFromFile("arial.ttf")) {
		std::cerr << "Failed to load font\n";
	}
	else
	{
		scoreText.setFont(scoreFont);
	}

	scoreText.setCharacterSize(40);
	scoreText.setString("0");
	scoreText.setPosition({ 0, -360 });

	background.setSize({ 1280.f, 720.f });
	background.setFillColor(sf::Color(30, 125, 189));
	background.setOrigin(background.getSize() / 2.f);
	reset();
}

void EntityManager::drawAll(sf::RenderWindow& window) {
	window.draw(background);
	bird.draw(window);
	obstacle1.draw(window);
	obstacle2.draw(window);

	// Overlay
	window.draw(scoreText);
}

void EntityManager::handleEvent(const sf::Event& event) {
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
		if (keyPressed->code == sf::Keyboard::Key::Space) {
			bird.jump(jumpForce);
		}
	}
}

void EntityManager::updateAll(float dt) {
	bird.update(dt);
	obstacle1.update(dt);
	obstacle2.update(dt);

	Obstacle& closerObstacle = getCloserObstacle();
	Pipe& top = closerObstacle.getTopPipe();
	Pipe& bottom = closerObstacle.getBottomPipe();

	if (bird.sprite.getGlobalBounds().findIntersection(top.sprite.getGlobalBounds()) ||
		bird.sprite.getGlobalBounds().findIntersection(bottom.sprite.getGlobalBounds())) {

		gameEngine->state = State::GameOver;
	}

	if (closerObstacle.getTopPipe().getPosition().x < bird.getPosition().x) {
		gameEngine->scoreManager.handle(closerObstacle);
	}

	//scoreText.setString(std::to_string(gameEngine->scoreManager.getScore()));
}

Bird& EntityManager::getBird() {
	return bird;
}

void EntityManager::updatePipeGap() {
	obstacle1.setGap(pipeGap);
	obstacle2.setGap(pipeGap);
}

Obstacle& EntityManager::getCloserObstacle() {
	if (obstacle1.getTopPipe().getPosition().x < obstacle2.getTopPipe().getPosition().x) {
		return obstacle1;
	}
	else {
		return obstacle2;
	}
}

void EntityManager::reset() {
	bird.reset();
	obstacle1.reset();
	obstacle2.reset();
}