#pragma once

#include "GameObject.h"
#include "Bird.h"
#include "Pipe.h"
#include <array>

class EntityManager
{
private:
	Bird bird;
	std::array<Pipe, 4> pipes;
public:
	EntityManager()
		: pipes{
			Pipe::TopPipe(true),
			Pipe::BottomPipe(true),

			Pipe::TopPipe(false),
			Pipe::BottomPipe(false)
		  }
	{}

	void drawAll(sf::RenderWindow& window) {
		bird.draw(window);
		for (auto& pipe : pipes) {
			pipe.draw(window);
		}
	}

	void handleEvent(const sf::Event& event) {
		if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Space) {
				bird.jump();
			}
		}
	}

	void updateAll(float dt) {
		bird.update(dt);
		for (auto& pipe : pipes) {
			pipe.update(dt);
		}
	}

private:
	std::array<Pipe, 4>::iterator getCloserPipe() {
		std::array<Pipe, 4>::iterator closerPipe = pipes.begin();
		for (auto it = pipes.begin(); it != pipes.end(); it+=2) {
			auto pipe = *it;
			if (pipe.getPosition().x < closerPipe->getPosition().x) {
				closerPipe = it;
			}
		}
		return closerPipe;
	}
};