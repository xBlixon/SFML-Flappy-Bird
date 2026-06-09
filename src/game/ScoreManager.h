#pragma once

#include "Obstacle.h"
#include <iostream>

class ScoreManager
{
private:
	sf::Text* scoreText = nullptr;
	bool hasScoredNow = false;
	int score = 0;

public:

	void setText(sf::Text* text) {
		scoreText = text;
	}

	int getScore() const {
		return score;
	}

	void handle(Obstacle& obstacle) {
		if (!obstacle.wasScored) {
			score++;
			obstacle.wasScored = true;

			if(scoreText == nullptr) {
				std::cerr << "Cannot update score display. scoreText set to nullptr.\n";
				return;
			}
			scoreText->setString(std::to_string(score));
		}
	}
};