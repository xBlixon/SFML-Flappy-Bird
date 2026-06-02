#pragma once

#include <random>
#include "Pipe.h"


class Obstacle
{
private:
	float verticalOffset;
	float resetBoundary = -20.f;
	float gap = 100.f;
	std::mt19937 rng{ std::random_device{}() };
	std::uniform_real_distribution<float> distribution{ 0.f, 100.f };

	Pipe topPipe;
	Pipe bottomPipe;

public:
	Obstacle(bool closer) 
		: topPipe (Pipe::TopPipe   (closer)), 
		bottomPipe(Pipe::BottomPipe(closer))
	{
		rerollVerticalOffset();
		topPipe.sprite.move(
			{
				0.f,
				verticalOffset - gap / 2
			}
		);
		bottomPipe.sprite.move(
			{
				0.f,
				verticalOffset + gap / 2
			}
		);
	};

	void draw(sf::RenderWindow& window) {
		topPipe.draw(window);
		bottomPipe.draw(window);
	}

	void rerollVerticalOffset() {
		verticalOffset = distribution(rng);
	}

	void setGap(float gap) {
		this->gap = gap;

		topPipe.sprite.setPosition(
			{
				topPipe.sprite.getPosition().x,
				verticalOffset - this->gap / 2
			}
		);

		bottomPipe.sprite.setPosition(
			{
				bottomPipe.sprite.getPosition().x,
				topPipe.sprite.getSize().y + this->gap/2 + verticalOffset
			}
			);
	}

	void update(float dt) {
		float resetPositionX = 400.f;
		topPipe.update(dt);
		bottomPipe.update(dt);
		if (topPipe.sprite.getPosition().x < resetBoundary) {
			rerollVerticalOffset();

			topPipe.sprite.setPosition(
				{
					resetPositionX,
					verticalOffset - this->gap / 2
				}
			);

			bottomPipe.sprite.setPosition(
				{ 
					resetPositionX,
					topPipe.sprite.getSize().y + gap/2 + verticalOffset 
				}
			);
		}
	}

	Pipe& getTopPipe() {
		return topPipe;
	}

	Pipe& getBottomPipe() {
		return bottomPipe;
	}

	void reset() {
		rerollVerticalOffset();
		topPipe.reset();
		bottomPipe.reset();
		setGap(gap); // Update vertical offset after resetting position
	}
};