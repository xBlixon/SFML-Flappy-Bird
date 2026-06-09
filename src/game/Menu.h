#pragma once

#include <iostream>
#include "GameObject.h"

class Menu : public GameObject
{
private:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape textBackground;

public:
	Menu(std::string fontPath) : text(font) {
		sprite.setSize({ 1280.f, 720.f });
		sprite.setOrigin(sprite.getSize() / 2.f);
		sprite.setPosition({ 0.f, 0.f });
		sprite.setFillColor(sf::Color(0, 0, 0, 70));

		if (!font.openFromFile(fontPath)) {
			std::cerr << "Failed to load font for Menu\n";
		}
		else
		{
			text.setFont(font);
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::White);

			textBackground.setFillColor(sf::Color(0, 0, 0, 150));
			displayMainMenu();
			/*sprite.setSize({ boundsSize.x + 20, boundsSize.y + 20 });
			sprite.setOrigin(sprite.getSize() / 2.f);
			sprite.setPosition({ 0.f, 0.f });
			sprite.setFillColor(sf::Color(0, 0, 0, 150));*/
		}
	}

	void update(float dt) override {
		// No update logic for the menu
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(textBackground);
		window.draw(text);
	}

	void displayGameOver() {
		text.setString("Game Over! Press Space to Restart");
		centerText();
	}
	
	void displayPaused() {
		text.setString("Press Space to Resume");
		centerText();
	}

	void displayMainMenu() {
		text.setString("Press Space to Start");
		centerText();
	}

private:
	void centerText() {
		sf::Vector2f boundsSize = text.getLocalBounds().size;
		text.setOrigin(boundsSize / 2.f);
		text.setPosition({ 0, 100 });

		textBackground.setSize(boundsSize + sf::Vector2f(20, 20));
		textBackground.setOrigin(textBackground.getSize() / 2.f);
		textBackground.setPosition(text.getPosition() + sf::Vector2f(0.f, 5.f));
	}
};