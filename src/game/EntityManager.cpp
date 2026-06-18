#pragma once

#define FONT "arial.ttf"

#include "EntityManager.h"
#include "GameEngine.h"
#include "State.h"
#include <iostream>
#include "utils/Concepts.h"
#include <algorithm>

EntityManager::EntityManager(GameEngine* gameEngine) :
	gravityForce(bird.gravityForce),
	jumpForce(bird.jumpForce),
	gameEngine(gameEngine),
	scoreText(scoreFont),
	menu(FONT, &gameEngine->scoreManager)
{
	gameEngine->scoreManager.setText(&scoreText); //Must be set 

	#if defined(_WIN32)
	if (!scoreFont.openFromFile(FONT) &&
		!scoreFont.openFromFile(fs::path("C:\\Windows\\Fonts\\arial.ttf"))) {
		std::cerr << "Failed to load font for score.\n";
	}
	#else
	if (!scoreFont.openFromFile(FONT)) {
		std::cerr << "Failed to load font\n";
	}
	#endif
	else
	{
		scoreText.setFont(scoreFont);
	}
	scoreText.setCharacterSize(40);

	background.setSize({ 1280.f, 720.f });
	background.setFillColor(sf::Color(30, 125, 189));
	background.setOrigin(background.getSize() / 2.f);
	reset();
}

void EntityManager::drawAll(sf::RenderWindow& window) {
	window.draw(background);
	drawComponent(bird, window);
	drawComponent(obstacle1, window);
	drawComponent(obstacle2, window);


	// Overlay
	window.draw(scoreText);

	if(gameEngine->state != State::Playing) {
		drawComponent(menu, window);
	}
}

template <Renderable T>
void EntityManager::drawComponent(T& component, sf::RenderWindow& window) {
	component.draw(window);
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
		bird.sprite.getGlobalBounds().findIntersection(bottom.sprite.getGlobalBounds()) ||
		bird.getPosition().y > 375.f // Fall to the ground
		) {

		gameEngine->gameOver();
		menu.updateHistory();
	}

	if (closerObstacle.getTopPipe().getPosition().x < bird.getPosition().x) {
		gameEngine->scoreManager.handle(closerObstacle);
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
	resetScoreText();
	menu.displayMainMenu();
	bird.reset();
	obstacle1.reset();
	obstacle2.reset();
}

void EntityManager::resetScoreText() {
	gameEngine->scoreManager.resetScore();
	scoreText.setString("Score: 0 Best: " + std::to_string(gameEngine->scoreManager.getHighScore()));
	sf::Vector2f boundsSize = scoreText.getLocalBounds().size;
	scoreText.setOrigin({ boundsSize.x / 2, 0 });
	scoreText.setPosition({ 0, -360 });
}

void EntityManager::pause() {
	menu.displayPaused();
}

void EntityManager::gameOver() {
	menu.displayGameOver();
}