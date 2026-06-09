#pragma once

#include "Obstacle.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>

namespace fs = std::filesystem;

class ScoreManager
{
private:
	sf::Text* scoreText = nullptr;
	bool hasScoredNow = false;
	int score = 0;
	int highScore = 0;
	fs::path highScorePath = "highscore.txt";

public:
	ScoreManager() {
		std::ifstream highScoreFile(highScorePath);
		if (highScoreFile.is_open()) {
			highScoreFile >> highScore;
			highScoreFile.close();
		}
	}

	void setText(sf::Text* text) {
		scoreText = text;
	}

	int getScore() const {
		return score;
	}

	int getHighScore() const {
		return highScore;
	}

	void resetScore() {
		score = 0;
	}

	void handle(Obstacle& obstacle) {
		if (!obstacle.wasScored) {
			score++;
			obstacle.wasScored = true;

			if(score > highScore) {
				highScore = score;
				save();
			}

			if(scoreText == nullptr) {
				std::cerr << "Cannot update score display. scoreText set to nullptr.\n";
				return;
			}

			scoreText->setString("Score: " + std::to_string(score) 
				+ " Best: " + std::to_string(highScore));

			sf::Vector2f boundsSize = scoreText->getLocalBounds().size;

			scoreText->setOrigin({boundsSize.x / 2, 0});
			scoreText->setPosition({ 0, -360 });
		}
	}

	void save() {
		int scoreToSave = highScore; // Memory-safe highscore snapshot

		std::thread([this, scoreToSave]() {
			std::ofstream highScoreFile(highScorePath);
			if (highScoreFile.is_open()) {
				highScoreFile << scoreToSave;
				highScoreFile.close();
			}
			}).detach();
	}
};