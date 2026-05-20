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
	{

	}

	void drawAll(sf::RenderWindow& window) {
		bird.draw(window);
		for (auto& pipe : pipes) {
			pipe.draw(window);
		}
	}

	void handleEvent(const sf::Event& event) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			bird.update(1.0f);
		}
	}

private:
	GameObject& getCloserPipe() {
		GameObject* closerPipe = &pipes[0];
		for (auto& pipe : pipes) {
			if (pipe.getPosition().x < closerPipe->getPosition().x) {
				closerPipe = &pipe;
			}
		}
		return *closerPipe;
	}
};