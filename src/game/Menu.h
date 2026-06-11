#pragma once

#include <iostream>
#include <ranges>
#include <filesystem>
#include "ScoreManager.h"
#include "GameObject.h"

namespace fs = std::filesystem;

class Menu : public GameObject
{
private:
	ScoreManager* scoreManager = nullptr;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape textBackground;

	sf::Text history;
	sf::RectangleShape historyBackground;

public:
	Menu(fs::path fontPath, ScoreManager* manager) : text(font), history(font), scoreManager(manager) {
		sprite.setSize({ 1280.f, 720.f });
		sprite.setOrigin(sprite.getSize() / 2.f);
		sprite.setPosition({ 0.f, 0.f });
		sprite.setFillColor(sf::Color(0, 0, 0, 70));

		#if defined(_WIN32)
		if (!font.openFromFile(fontPath) && 
			!font.openFromFile(fs::path("C:\\Windows\\Fonts\\arial.ttf")) ) {
			std::cerr << "Failed to load font for Menu.\n";
		}
		#else
		if (!font.openFromFile(fontPath)) {
			std::cerr << "Failed to load font for Menu.\n";
		}
		#endif
		else
		{
			text.setFont(font);
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::White);

			textBackground.setFillColor(sf::Color(0, 0, 0, 150));
			displayMainMenu();

			history.setFont(font);
			history.setCharacterSize(20);
			history.setFillColor(sf::Color::White);

			historyBackground.setFillColor(sf::Color(0, 0, 0, 150));

			updateHistory();
		}
	}

	void update(float dt) override {
		// No update logic for the menu
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(textBackground);
		window.draw(text);

		window.draw(historyBackground);
		window.draw(history);
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

	void updateHistory() {
		if (!scoreManager) return;

		const auto& fullHistory = scoreManager->getHistory();
		if (fullHistory.empty()) return;

		auto lastFiveGames = fullHistory
			| std::views::reverse
			| std::views::take(5);

		std::string historyString = "Recent game history:\n";
		int index = 1;

		for (const auto& game : lastFiveGames) {
			historyString += std::to_string(index++) + ". ["
				+ game.getDateTime() + "] Score: "
				+ std::to_string(game.getScore()) + "\n";
		}

		history.setString(historyString);

		history.setPosition({ -620.f, -340.f });

		sf::Vector2f boundsSize = history.getLocalBounds().size;
		historyBackground.setSize(boundsSize + sf::Vector2f(20.f, 10.f));
		historyBackground.setPosition(history.getPosition() - sf::Vector2f(10.f, 10.f));
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