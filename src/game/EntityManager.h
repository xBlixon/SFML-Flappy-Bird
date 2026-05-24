#pragma once

#include "GameObject.h"
#include "Bird.h"
#include "Pipe.h"
#include "Obstacle.h"
#include <array>

class EntityManager
{
private:
	Bird bird;
	Obstacle obstacle1{ true  };
	Obstacle obstacle2{ false };
public:
	float pipeGap = 100.f;
	float jumpForce = 50.f;
	float &gravityForce;

	EntityManager()
		: gravityForce(bird.gravityForce)
	{
	}

	void drawAll(sf::RenderWindow& window) {
		bird.draw(window);
		obstacle1.draw(window);
		obstacle2.draw(window);
	}

	void handleEvent(const sf::Event& event) {
		if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Space) {
				bird.jump(jumpForce);
			}
		}
	}

	void updateAll(float dt) {
		bird.update(dt);
		obstacle1.update(dt);
		obstacle2.update(dt);
	}

	Bird& getBird() {
		return bird;
	}

	void updatePipeGap() {
		obstacle1.setGap(pipeGap);
		obstacle2.setGap(pipeGap);
	}
};