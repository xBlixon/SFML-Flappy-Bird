#pragma once

#include "Obstacle.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>

#include "GameResult.h"

namespace fs = std::filesystem;

class ScoreManager
{
private:
	sf::Text* scoreText = nullptr;
	bool hasScoredNow = false;
	int score = 0;
	int highScore = 0;
	fs::path highScorePath = "highscore.txt";

	std::vector<GameResult> history;
	fs::path historyPath = "history.txt";

public:
	ScoreManager() {
		std::ifstream highScoreFile(highScorePath);
		if (highScoreFile.is_open()) {
			highScoreFile >> highScore;
			highScoreFile.close();
		}

		std::ifstream historyFile(historyPath);
		std::string line;
		while (std::getline(historyFile, line)) {
			std::stringstream ss(line);
			std::string scoreStr, dateStr;
			if (std::getline(ss, scoreStr, ',') && std::getline(ss, dateStr)) {
				history.push_back(GameResult(std::stoi(scoreStr), dateStr));
			}
		}
		historyFile.close();
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

	void addCurrentGameToHistory() {
		auto now = std::chrono::system_clock::now();
		auto timeT = std::chrono::system_clock::to_time_t(now);
		std::tm tmBuffer;

		#if defined(_MSC_VER)
		localtime_s(&tmBuffer, &timeT);
		#else
		localtime_r(&timeT, &tmBuffer);
		#endif

		std::stringstream ss;
		ss << std::put_time(&tmBuffer, "%Y-%m-%d %H:%M:%S");

		history.push_back({ score, ss.str() });

		saveHistoryAsync();
	}

	const std::vector<GameResult>& getHistory() const {
		return history;
	}

private:
	void saveHistoryAsync() {
		std::vector<GameResult> historyCopy = history;

		std::thread([this, historyCopy]() {
			std::ofstream historyFile(historyPath);
			if (historyFile.is_open()) {
				for (const auto& entry : historyCopy) {
					historyFile << entry.getScore() << "," << entry.getDateTime() << "\n";
				}
				historyFile.close();
			}
			}).detach();
	}
};