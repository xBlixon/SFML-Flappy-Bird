#pragma once

#include "GameObject.h"

class Bird : public GameObject
{
	float verticalVelocity = 0.f;

public:
	Bird() {
		sprite.setSize({ 20.f, 20.f });
		sprite.setFillColor(sf::Color::Yellow);
	}

	void update(float dt) override {
		sprite.move({ 0.f, -verticalVelocity * dt });
		verticalVelocity -= 100.f * dt;
	}

	void jump() {
		verticalVelocity = 100.f;
	}
};