#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f position;
	sf::Sprite sprite;
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};