#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class GameObject {
public:
	sf::RectangleShape sprite;

	virtual void update(float dt) = 0;
	//virtual void draw(sf::RenderWindow& window) = 0;

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	sf::Vector2f getPosition() const {
		return sprite.getPosition();
	};

	void setPosition(sf::Vector2f pos) {
		sprite.setPosition(pos);
	};

	//virtual void move(sf::Vector2f offset) = 0;
};