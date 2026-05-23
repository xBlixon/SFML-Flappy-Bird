#pragma once

#include "GameObject.h"

class Pipe : public GameObject
{
private:
	Pipe() {
		sprite.setSize({ 20.f, 50.f });
		sprite.setFillColor(sf::Color::Green);
	}
public:
	void update(float dt) override {
		sprite.move({ -100.f * dt, 0.f });
		if(sprite.getPosition().x < -20.f) {
			sprite.setPosition({ 400.f, sprite.getPosition().y });
		}
	}

	static Pipe TopPipe(bool closer) {
		Pipe pipe;
		pipe.sprite.setPosition(
			{
				closer ? 200.f : 400.f
				, 
				0.f
			}
		);
		return pipe;
	}

	static Pipe BottomPipe(bool closer) {
		Pipe pipe;
		pipe.sprite.setPosition(
			{
				closer ? 200.f : 400.f
				,
				150.f
			}
		);
		return pipe;
	}

};