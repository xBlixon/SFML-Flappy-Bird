#pragma once

#include "GameObject.h"

class Bird : public GameObject
{
public:
	Bird() {
		sprite.setSize({ 20.f, 20.f });
		sprite.setFillColor(sf::Color::Yellow);
	}

	void update(float dt) override {
		sprite.move({ 0.f, -1.f * dt });
	}
};