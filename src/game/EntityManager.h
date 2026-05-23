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
	float BottomPipeY;
	float jumpVelocity = 50.f;
	float &gravityForce;

	EntityManager()
		: pipes{
			Pipe::TopPipe(true),
			Pipe::BottomPipe(true),

			Pipe::TopPipe(false),
			Pipe::BottomPipe(false)
		}, gravityForce(bird.gravityForce)
	{
		BottomPipeY = pipes[1].getPosition().y;
	}

	void drawAll(sf::RenderWindow& window) {
		bird.draw(window);
		for (auto& pipe : pipes) {
			pipe.draw(window);
		}
	}

	void handleEvent(const sf::Event& event) {
		if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Space) {
				bird.jump(jumpVelocity);
			}
		}
	}

	void updateAll(float dt) {
		bird.update(dt);
		for (auto& pipe : pipes) {
			pipe.update(dt);
		}
	}

	Bird& getBird() {
		return bird;
	}

	std::array<Pipe, 4>& getPipes() {
		return pipes;
	}

	void updateHeightOfBottomPipes() {
		auto& p1 = pipes[1];
		auto& p2 = pipes[3];
		p1.setPosition({ p1.getPosition().x, BottomPipeY });
		p2.setPosition({ p2.getPosition().x, BottomPipeY });
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