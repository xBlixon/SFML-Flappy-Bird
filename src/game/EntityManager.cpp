#pragma once

#include "EntityManager.h"
#include "GameEngine.h"
#include "State.h"

EntityManager::EntityManager(GameEngine* gameEngine)
	: gravityForce(bird.gravityForce),
	  jumpForce(bird.jumpForce),
	  gameEngine(gameEngine)
{
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

	Obstacle closerObstacle = getCloserObstacle();
	Pipe top = closerObstacle.getTopPipe();
	Pipe bottom = closerObstacle.getBottomPipe();

	if (bird.sprite.getGlobalBounds().findIntersection(top.sprite.getGlobalBounds()) ||
		bird.sprite.getGlobalBounds().findIntersection(bottom.sprite.getGlobalBounds())) {

		gameEngine->state = State::GameOver;
	}
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