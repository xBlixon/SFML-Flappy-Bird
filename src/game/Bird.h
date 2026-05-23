#pragma once

#include "GameObject.h"

class Bird : public GameObject
{
public:
	float verticalVelocity = 0.f;
	float gravityForce = 100.f;

	Bird() {
		sprite.setSize({ 20.f, 20.f });
		sprite.setFillColor(sf::Color::Yellow);
	}

	void update(float dt) override {
		sprite.move({ 0.f, -verticalVelocity * dt });
		verticalVelocity -= gravityForce * dt;
	}

	void jump(float velocity) {
		verticalVelocity = velocity;
	}
};